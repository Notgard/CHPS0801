#include <iostream>
#include <unistd.h>

#include "gaussianNoise.h"

using namespace cv;
using namespace std;

#define NOISE_ITER 15
#define ITERATIONS 15
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
                             "{@input   |../../img/img.jpg|input image}");
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
        ViewImageType::HostMirror host_img_in = Kokkos::create_mirror_view(img_in);
        ViewImageType::HostMirror host_img_out = Kokkos::create_mirror_view(img_out);

        // initialize both views with data
        int stride = 1;
        // auto full_image = Kokkos::MDRangePolicy<Kokkos::Rank<3>>({0, 0, 0}, {image_pad.rows, image_pad.cols, cn}, {stride, stride, stride});
        auto full_image = Kokkos::MDRangePolicy<Kokkos::Rank<2>>({0, 0}, {image_pad.rows, image_pad.cols}, {stride, stride});

        cout << "Initializing kokkos in and out views" << endl;

        // CUDA VERSION INITIALIZATION
        for (int i = 0; i < image_pad.rows; i++)
        {
            for (int j = 0; j < image_pad.cols; j++)
            {
                int index = i * image_pad.cols * cn + j * cn;
                host_img_in(i, j, 0) = pixelPtr[index + 0]; // B
                host_img_in(i, j, 1) = pixelPtr[index + 1]; // G
                host_img_in(i, j, 2) = pixelPtr[index + 2]; // R
                host_img_out(i, j, 0) = 0;                  // initialize output image as black
                host_img_out(i, j, 1) = 0;                  // initialize output image as black
                host_img_out(i, j, 2) = 0;                  // initialize output image as black
            }
        }

        Kokkos::deep_copy(img_in, host_img_in);
        Kokkos::deep_copy(img_out, host_img_out);
        /*
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
         */
        cout << "finished init, starting jacobi filter" << endl;

        ///////////////////////////////////////////////////////
        // Convert the image (image_pad) to jacobi 5 way stenciled using Kokkos device views
        ///////////////////////////////////////////////////////

        auto gauss_original_image = Kokkos::MDRangePolicy<Kokkos::Rank<3>>({1, 1, 0}, {image_pad.rows - 1, image_pad.cols - 1, cn}, {stride, stride, stride});
        // auto original_image = Kokkos::MDRangePolicy<Kokkos::Rank<2>>({0, 0}, {img.rows, img.cols}, {stride, stride});

        int diagonals = 2 * n - 1, i, j;

        // Timer products.
        Kokkos::Timer timer;

        for (int iter = 0; iter < ITERATIONS; iter++)
        {
            for (int k = 1; k <= diagonals; k++)
            {
                auto diagonal_range = Kokkos::RangePolicy<>(0, (k < n ? k : n));
                Kokkos::parallel_for("apply_gauss_diag", diagonal_range, KOKKOS_LAMBDA(int idx) {
                    int i = (k <= n ? 1 + idx : k - n + 1 + idx);
                    if (i <= n) {
                        int j = k + 1 - i;
                        img_out(i, j, 0) = 0.2 * (img_in(i, j, 0) + img_in(i, j - 1, 0) + img_in(i - 1, j, 0) + img_in(i, j + 1, 0) + img_in(i + 1, j, 0));
                        img_out(i, j, 1) = 0.2 * (img_in(i, j, 1) + img_in(i, j - 1, 1) + img_in(i - 1, j, 1) + img_in(i, j + 1, 1) + img_in(i + 1, j, 1));
                        img_out(i, j, 2) = 0.2 * (img_in(i, j, 2) + img_in(i, j - 1, 2) + img_in(i - 1, j, 2) + img_in(i, j + 1, 2) + img_in(i + 1, j, 2));
                    }
                });
            }
            Kokkos::fence();
            Kokkos::deep_copy(img_in, img_out);
        }

        // Calculate time.
        double time = timer.seconds();

        Kokkos::deep_copy(host_img_out, img_out);

        ///////////////////////////////////////////////
        // Copy back view memory from device to host to write the image back using opencv
        ///////////////////////////////////////////////

        auto original_image = Kokkos::MDRangePolicy<Kokkos::Rank<2>>({0, 0}, {img.rows, img.cols}, {stride, stride});

        /*         Kokkos::parallel_for("output_image", original_image, KOKKOS_LAMBDA(int i, int j) {
                    int index = i * image_pad.cols * cn + j * cn;
                    //pixelPtr[index + k] = img_out(i, j, k);
                    pixelPtr[index + 0] = img_out(i, j, 0); // B
                    pixelPtr[index + 1] = img_out(i, j, 1); // G
                    pixelPtr[index + 2] = img_out(i, j, 2); // R
                });
                Kokkos::fence(); */

        // CUDA COPY BACK DATA
        for (int i = 0; i < image_pad.rows; i++)
        {
            for (int j = 0; j < image_pad.cols; j++)
            {
                int index = i * image_pad.cols * cn + j * cn;
                pixelPtr[index + 0] = host_img_out(i, j, 0); // B
                pixelPtr[index + 1] = host_img_out(i, j, 1); // G
                pixelPtr[index + 2] = host_img_out(i, j, 2); // R
            }
        }

        // Calculate bandwidth.
        double Gbytes = 1.0e-9 * double(sizeof(uint8_t) * (img.rows * img.cols * cn * 4 * ITERATIONS));

        // Print results (problem size, time and bandwidth in GB/s).
        printf("time( %g s ) bandwidth( %g GB/s )\n",
               time, Gbytes / time);
    }
    Kokkos::finalize();

    fprintf(stdout, "Writting the output image of size %dx%d...\n", img.rows, img.cols);

    cv::Rect roi(PADDING, PADDING, image_pad.cols - PADDING - PADDING, image_pad.rows - PADDING - PADDING);
    cv::Mat image_no_pad = image_pad(roi).clone();
    fprintf(stdout, "Removed padding from %dx%d to %dx%d...\n", image_pad.rows, image_pad.cols, image_no_pad.rows, image_no_pad.cols);

    imwrite("../../res/gauss_diag_res.jpg", image_no_pad);
    imwrite("../../res/gauss_diag_noised_res.jpg", mColorNoise);
    return 0;
}