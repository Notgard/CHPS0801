#include <iostream>
// #include <vector>
// #include <algorithm>

#include "gaussianNoise.h"

using namespace cv;
using namespace std;

#define NOISE_ITER 15
#define PADDING 1
#define GREYSCALE 0

int main(int argc, char **argv)
{
    CommandLineParser parser(argc, argv,
                             "{@input   |../img/lena.jpg|input image}");
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

    ///////////////////////////////////////////////////////
    // Convert the image (image_pad) to grayscale using pixelPtr
    ///////////////////////////////////////////////////////

    uint8_t *pixelPtr = (uint8_t *)image_pad.data;
    int cn = image_pad.channels();

    if (GREYSCALE)
    {
        for (int i = 1; i < img.rows; i++)
        {
            for (int j = 1; j < img.cols; j++)
            {
                uint8_t b = pixelPtr[i * img.cols * cn + j * cn + 0]; // B
                uint8_t g = pixelPtr[i * img.cols * cn + j * cn + 1]; // G
                uint8_t r = pixelPtr[i * img.cols * cn + j * cn + 2]; // R

                uint8_t grey = r * 0.299 + g * 0.587 + b * 0.114;

                pixelPtr[i * img.cols * cn + j * cn + 0] = grey; // B
                pixelPtr[i * img.cols * cn + j * cn + 1] = grey; // G
                pixelPtr[i * img.cols * cn + j * cn + 2] = grey; // R
            }
        }
    }

    ///////////////////////////////////////////////////////
    // Convert the image (image_pad) to gauss-seidel 5 way stenciled using pixelPtr
    ///////////////////////////////////////////////////////

    // apply gauss seidel on color image
    for (int i = 1; i < img.rows; i++)
    {
        for (int j = 1; j < img.cols; j++)
        {
            //current pixel
            uint8_t b = pixelPtr[i * img.cols * cn + j * cn + 0];
            uint8_t g = pixelPtr[i * img.cols * cn + j * cn + 1];
            uint8_t r = pixelPtr[i * img.cols * cn + j * cn + 2];

            // up
            uint8_t up_b = pixelPtr[(i - 1) * img.cols * cn + j * cn + 0];
            uint8_t up_g = pixelPtr[(i - 1) * img.cols * cn + j * cn + 1];
            uint8_t up_r = pixelPtr[(i - 1) * img.cols * cn + j * cn + 2];

            // down
            uint8_t down_b = pixelPtr[(i + 1) * img.cols * cn + j * cn + 0];
            uint8_t down_g = pixelPtr[(i + 1) * img.cols * cn + j * cn + 1];
            uint8_t down_r = pixelPtr[(i + 1) * img.cols * cn + j * cn + 2];

            // left
            uint8_t left_b = pixelPtr[i * img.cols * cn + (j - 1) * cn + 0];
            uint8_t left_g = pixelPtr[i * img.cols * cn + (j - 1) * cn + 1];
            uint8_t left_r = pixelPtr[i * img.cols * cn + (j - 1) * cn + 2];
            
            // right
            uint8_t right_b = pixelPtr[i * img.cols * cn + (j + 1) * cn + 0];
            uint8_t right_g = pixelPtr[i * img.cols * cn + (j + 1) * cn + 1];
            uint8_t right_r = pixelPtr[i * img.cols * cn + (j + 1) * cn + 2];

            // get the average of the neighbors
            uint8_t avg_b = ((up_b + left_b) + (down_b + right_b + b)) / 5;
            uint8_t avg_g = ((up_g + left_g) + (down_g + right_g + g)) / 5;
            uint8_t avg_r = ((up_r + left_r) + (down_r + right_r + r)) / 5;

            pixelPtr[i * img.cols * cn + j * cn + 0] = avg_b;
            pixelPtr[i * img.cols * cn + j * cn + 1] = avg_g;
            pixelPtr[i * img.cols * cn + j * cn + 2] = avg_r;
        }
    }

    fprintf(stdout, "Writting the output image of size %dx%d...\n", img.rows, img.cols);

    imwrite("../res/gauss_seidel_res.jpg", image_pad);
    imwrite("../res/noised_res.jpg", mColorNoise);
    return 0;
}
