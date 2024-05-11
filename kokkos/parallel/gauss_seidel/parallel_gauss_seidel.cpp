#include <iostream>
#include <unistd.h>

#include "gaussianNoise.h"

using namespace cv;
using namespace std;

#define NOISE_ITER 15
#define PADDING 1

#define RED 1
#define BLACK 0

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

    ///////////////////////////////////////////////
    // Add noise to the image
    ///////////////////////////////////////////////

    Mat mColorNoise(img.size(), img.type());

    for (int i = 0; i < NOISE_ITER; ++i)
    {
        AddGaussianNoise(img, mColorNoise, 0, 30.0);
        if (i < (NOISE_ITER - 1))
        {
            uint8_t *tmp = img.data;
            img.data = mColorNoise.data;
            mColorNoise.data = tmp;
        }
    }

    // add padding to the image
    Mat image_pad;
    copyMakeBorder(img, image_pad, PADDING, PADDING, PADDING, PADDING, BORDER_CONSTANT, Scalar(0));

    // retrieve the pointer to the pixel data
    uint8_t *pixelPtr = (uint8_t *)image_pad.data;
    int cn = image_pad.channels();

    // get total image size
    size_t pad_image_size = image_pad.rows * image_pad.cols * cn;
    size_t original_image_size = img.rows * img.cols * cn;
    // dynamic allocation for image out data (size of original image without padding)
    // uint8_t *image_out = new uint8_t[img.rows * img.cols * cn];

    ///////////////////////////////////////////////
    // Manage Kokkos allocations
    ///////////////////////////////////////////////

    Kokkos::initialize(argc, argv);
    {

#ifdef KOKKOS_ENABLE_CUDA
#define MemSpace Kokkos::CudaSpace
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
        typedef Kokkos::View<uint8_t ***, Kokkos::LayoutLeft, MemSpace> ViewImageType;

        // allocate image in and image out
        ViewImageType img_in("image_pad", image_pad.rows, image_pad.cols, cn);
        ViewImageType img_out("image_out", image_pad.rows, image_pad.cols, cn);

        // create host mirrors of device views to write the image back from the host using opencv
        // ViewImageType::HostMirror img_in_host = Kokkos::create_mirror_view(img_in);
        // ViewImageType::HostMirror img_out_host = Kokkos::create_mirror_view(img_out);

        // initialize both views with data
        int stride = 1;
        //auto full_image = Kokkos::MDRangePolicy<Kokkos::Rank<3>>({0, 0, 0}, {image_pad.rows, image_pad.cols, cn}, {stride, stride, stride});
        auto full_image = Kokkos::MDRangePolicy<Kokkos::Rank<2>>({0, 0}, {image_pad.rows, image_pad.cols}, {stride, stride});

        cout << "Initializing kokkos in and out views" << endl;

        Kokkos::parallel_for("init_image", full_image, KOKKOS_LAMBDA(int i, int j) {
            int index = i * image_pad.cols * cn + j * cn;
            //img_in(i, j, k) = pixelPtr[index + k];
            img_in(i, j,  0) = pixelPtr[index + 0]; // B
            img_in(i, j,  1) = pixelPtr[index + 1]; // G
            img_in(i, j,  2) = pixelPtr[index + 2]; // R
            img_out(i, j, 0) = 0;                  // initialize output image as black
            img_out(i, j, 1) = 0;                  // initialize output image as black
            img_out(i, j, 2) = 0;                  // initialize output image as black
        });
        Kokkos::fence();

        cout << "finished init, starting jacobi filter" << endl;

        ///////////////////////////////////////////////////////
        // Convert the image (image_pad) to jacobi 5 way stenciled using Kokkos device views
        ///////////////////////////////////////////////////////

        auto gauss_original_image = Kokkos::MDRangePolicy<Kokkos::Rank<3>>({1, 1, 0}, {img.rows-1, img.cols-1, cn}, {stride, stride, stride});
        //auto original_image = Kokkos::MDRangePolicy<Kokkos::Rank<2>>({0, 0}, {img.rows, img.cols}, {stride, stride});

        // Timer products.
        Kokkos::Timer timer;

        Kokkos::parallel_for("apply_gauss_red", gauss_original_image, KOKKOS_LAMBDA(int i, int j, int k) {
            if((i + j) % 2 == RED) {
                uint8_t pixel = img_in(i, j, k);
                uint8_t left = img_in(i, j - 1, k);
                uint8_t right = img_in(i, j + 1, k);
                uint8_t up = img_in(i - 1, j, k);
                uint8_t down = img_in(i + 1, j, k);
                img_out(i, j, k) = (pixel + left + right + up + down) * 0.2;
            } 
        });
        Kokkos::fence();

        cout << "finished red gauss seidel..." << endl;

        Kokkos::parallel_for("apply_gauss_black", gauss_original_image, KOKKOS_LAMBDA(int i, int j, int k) {
            if((i + j) % 2 == BLACK) {
                uint8_t pixel = img_in(i, j, k);
                uint8_t left = img_in(i, j - 1, k);
                uint8_t right = img_in(i, j + 1, k);
                uint8_t up = img_in(i - 1, j, k);
                uint8_t down = img_in(i + 1, j, k);
                img_out(i, j, k) = (pixel + left + right + up + down) * 0.2;
            } 
        });
        Kokkos::fence();
        cout << "finished black gauss seidel..." << endl;

        // Calculate time.
        double time = timer.seconds();

        ///////////////////////////////////////////////
        // Copy back view memory from device to host to write the image back using opencv
        ///////////////////////////////////////////////

        auto original_image = Kokkos::MDRangePolicy<Kokkos::Rank<2>>({0, 0}, {img.rows, img.cols}, {stride, stride});

        Kokkos::parallel_for("output_image", original_image, KOKKOS_LAMBDA(int i, int j) {
            int index = i * image_pad.cols * cn + j * cn;
            //pixelPtr[index + k] = img_out(i, j, k); 
            pixelPtr[index + 0] = img_out(i, j, 0); // B
            pixelPtr[index + 1] = img_out(i, j, 1); // G
            pixelPtr[index + 2] = img_out(i, j, 2); // R
        });
        Kokkos::fence();

        // Calculate bandwidth.
        double Gbytes = 1.0e-9 * double(sizeof(uint8_t) * (img.rows * img.cols * cn * 4));

        // Print results (problem size, time and bandwidth in GB/s).
        printf("time( %g s ) bandwidth( %g GB/s )\n",
               time, Gbytes / time);
    }
    Kokkos::finalize();

    fprintf(stdout, "Writting the output image of size %dx%d...\n", img.rows, img.cols);

    cv::Rect roi(PADDING, PADDING, image_pad.cols - PADDING - PADDING, image_pad.rows - PADDING - PADDING);
    cv::Mat image_no_pad = image_pad(roi).clone();
    fprintf(stdout, "Removed padding from %dx%d to %dx%d...\n", image_pad.rows, image_pad.cols, image_no_pad.rows, image_no_pad.cols);

    imwrite("../../res/kokkos_parallel_gauss_seidel_res.jpg", image_no_pad);
    imwrite("../../res/kokkos_parallel_gauss_seidel_noised_res.jpg", mColorNoise);
    return 0;
}