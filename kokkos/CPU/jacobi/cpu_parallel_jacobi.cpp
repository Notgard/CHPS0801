#include <iostream>
#include <unistd.h>

#include "gaussianNoise.h"

using namespace cv;
using namespace std;

#define NOISE_ITER 15
#define PADDING 1

#include <Kokkos_Core.hpp>

int main(int argc, char **argv)
{
    char buffer[1024];
    if (getcwd(buffer, sizeof(buffer)) != NULL)
    {
        std::cout << "Current Directory: " << buffer << std::endl;
    }
    else
    {
        perror("getcwd() error");
        return 1;
    }

    CommandLineParser parser(argc, argv,
                             "{@input   |../../img/lena.jpg|input image}");
    parser.printMessage();

    String imageName = parser.get<String>("@input");
    string image_path = samples::findFile(imageName);
    Mat img = imread(image_path, IMREAD_COLOR);
    if (img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }

    // add padding to the image
    Mat image_pad;
    copyMakeBorder(img, image_pad, PADDING, PADDING, PADDING, PADDING, BORDER_CONSTANT, Scalar(0));

    ///////////////////////////////////////////////
    // Add noise to the image
    ///////////////////////////////////////////////

    Mat mColorNoise(image_pad.size(), image_pad.type());

    for (int i = 0; i < NOISE_ITER; ++i)
    {
        AddGaussianNoise(image_pad, mColorNoise, 0, 30.0);
        if (i < (NOISE_ITER - 1))
        {
            uint8_t *tmp = image_pad.data;
            image_pad.data = mColorNoise.data;
            mColorNoise.data = tmp;
        }
    }

    // create clone of image
    // Mat image_out = image_pad.clone();

    // retrieve the pointer to the pixel data
    uint8_t *pixelPtr = (uint8_t *)image_pad.data;
    int cn = image_pad.channels();

    // get total image size
    size_t image_size = image_pad.rows * image_pad.cols * cn;
    // dynamic allocation for image out data
    uint8_t *image_out = new uint8_t[image_size];

    ///////////////////////////////////////////////
    // Manage Kokkos allocations
    ///////////////////////////////////////////////

    Kokkos::initialize(argc, argv);
    {

#ifdef KOKKOS_ENABLE_CUDA
#define MemSpace Kokkos::CudaSpace
#endif
#ifdef KOKKOS_ENABLE_HIP
#define MemSpace Kokkos::Experimental::HIPSpace
#endif
#ifdef KOKKOS_ENABLE_OPENMPTARGET
#define MemSpace Kokkos::OpenMPTargetSpace
#endif

#ifndef MemSpace
#define MemSpace Kokkos::HostSpace
#endif

        using ExecSpace = MemSpace::execution_space;
        using range_policy = Kokkos::RangePolicy<ExecSpace>;

        // define view
        typedef Kokkos::View<uint8_t *, Kokkos::LayoutLeft, MemSpace> ViewImageType;

        // allocate image in and image out
        ViewImageType img_in("image_pad", image_size);
        ViewImageType img_out("image_out", image_size);

        // create host mirrors of device views to write the image back from the host using opencv
        ViewImageType::HostMirror img_in_host = Kokkos::create_mirror_view(img_in);
        ViewImageType::HostMirror img_out_host = Kokkos::create_mirror_view(img_out);

        // initialize both views with data
        int stride = 1;
        auto full_image = Kokkos::MDRangePolicy<Kokkos::Rank<2>>({0, 0}, {image_pad.rows, image_pad.cols * cn}, {stride, stride});

        Kokkos::parallel_for("init_image", full_image, KOKKOS_LAMBDA(int i, int j) {
            int index = i * img.cols * cn + j * cn;
            img_in(i * img.cols * cn * j * cn + 0) = pixelPtr[index + 0]; // B
            img_in(i * img.cols * cn * j * cn + 1) = pixelPtr[index + 1]; // G
            img_in(i * img.cols * cn * j * cn + 2) = pixelPtr[index + 2]; // R
            img_out(i * img.cols * cn * j * cn + 0) = 0;                  // initialize output image as black
            img_out(i * img.cols * cn * j * cn + 1) = 0;                  // initialize output image as black
            img_out(i * img.cols * cn * j * cn + 2) = 0;                  // initialize output image as black
        });
        Kokkos::fence();

        ///////////////////////////////////////////////////////
        // Convert the image (image_pad) to jacobi 5 way stenciled using Kokkos device views
        ///////////////////////////////////////////////////////

        Kokkos::parallel_for("apply_jacobi", full_image, KOKKOS_LAMBDA(int i, int j) {
            int index = i * img.cols * cn * j * cn;
            // current pixel
            uint8_t b = img_in(index + 0);
            uint8_t g = img_in(index + 1);
            uint8_t r = img_in(index + 2);

            // left red
            uint8_t left_r = img_in(i * img.cols * cn * (j - 1) * cn + 2);
            // left green
            uint8_t left_g = img_in(i * img.cols * cn * (j - 1) * cn + 1);
            // left blue
            uint8_t left_b = img_in(i * img.cols * cn * (j - 1) * cn + 0);

            // right red
            uint8_t right_r = img_in(i * img.cols * cn * (j + 1) * cn + 2);
            // right green
            uint8_t right_g = img_in(i * img.cols * cn * (j + 1) * cn + 1);
            // right blue
            uint8_t right_b = img_in(i * img.cols * cn * (j + 1) * cn + 0);

            // up red
            uint8_t up_r = img_in((i - 1) * img.cols * cn * j * cn + 2);
            // up green
            uint8_t up_g = img_in((i - 1) * img.cols * cn * j * cn + 1);
            // up blue
            uint8_t up_b = img_in((i - 1) * img.cols * cn * j * cn + 0);

            // down red
            uint8_t down_r = img_in((i + 1) * img.cols * cn * j * cn + 2);
            // down green
            uint8_t down_g = img_in((i + 1) * img.cols * cn * j * cn + 1);
            // down blue
            uint8_t down_b = img_in((i + 1) * img.cols * cn * j * cn + 0);

            // average the pixel values
            uint8_t avg_r = (r + left_r + right_r + up_r + down_r) / 5;
            uint8_t avg_g = (g + left_g + right_g + up_g + down_g) / 5;
            uint8_t avg_b = (b + left_b + right_b + up_b + down_b) / 5;

            // update the pixel
            img_out(index + 0) = avg_b; // B
            img_out(index + 1) = avg_g; // G
            img_out(index + 2) = avg_r; // R
        });

        ///////////////////////////////////////////////
        // Copy back view memory from device to host to write the image back using opencv
        ///////////////////////////////////////////////

        Kokkos::deep_copy(img_in_host, img_in);
        Kokkos::deep_copy(img_out_host, img_out);

        Kokkos::parallel_for("output_image", full_image, KOKKOS_LAMBDA(int i, int j) {
            int index = i * img.cols * cn + j * cn;
            pixelPtr[index + 0] = img_out(index + 0); // B
            pixelPtr[index + 1] = img_out(index + 1); // G
            pixelPtr[index + 2] = img_out(index + 2); // R
        });
        Kokkos::fence();
    }
    Kokkos::finalize();

    fprintf(stdout, "Writting the output image of size %dx%d...\n", img.rows, img.cols);

    imwrite("../../res/kokkos_cpu_jacobi_res.jpg", image_pad);
    imwrite("../../res/kokkos_cpu_noised_res.jpg", mColorNoise);
    return 0;
}
