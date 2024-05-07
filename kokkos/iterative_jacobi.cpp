#include <iostream>
//#include <vector>
//#include <algorithm>

#include "gaussianNoise.h"

using namespace cv;
using namespace std;

#define NOISE_ITER 15
#define PADDING 1

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

    //add padding to the image
    Mat image_pad;
    copyMakeBorder(img,image_pad, PADDING, PADDING, PADDING, PADDING, BORDER_CONSTANT, Scalar(0));

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
    // Convert the image (image_pad) to jacobi 5 way stenciled using pixelPtr
    ///////////////////////////////////////////////////////

    uint8_t *pixelPtr = (uint8_t *)image_pad.data;
    int cn = image_pad.channels();

    for (int i = 0; i < img.rows+4; i++)
    {
        for (int j = 0; j < img.cols+4; j++)
        {
            uint8_t b = pixelPtr[i * img.cols * cn + j * cn + 0]; // B
            uint8_t g = pixelPtr[i * img.cols * cn + j * cn + 1]; // G
            uint8_t r = pixelPtr[i * img.cols * cn + j * cn + 2]; // R

            //left red
            uint8_t left_r = pixelPtr[i * img.cols * cn + (j - 1) * cn + 2];
            //left green
            uint8_t left_g = pixelPtr[i * img.cols * cn + (j - 1) * cn + 1];
            //left blue
            uint8_t left_b = pixelPtr[i * img.cols * cn + (j - 1) * cn + 0];

            //right red
            uint8_t right_r = pixelPtr[i * img.cols * cn + (j + 1) * cn + 2];
            //right green
            uint8_t right_g = pixelPtr[i * img.cols * cn + (j + 1) * cn + 1];
            //right blue
            uint8_t right_b = pixelPtr[i * img.cols * cn + (j + 1) * cn + 0];

            //up red
            uint8_t up_r = pixelPtr[(i - 1) * img.cols * cn + j * cn + 2];
            //up green
            uint8_t up_g = pixelPtr[(i - 1) * img.cols * cn + j * cn + 1];
            //up blue
            uint8_t up_b = pixelPtr[(i - 1) * img.cols * cn + j * cn + 0];

            //down red
            uint8_t down_r = pixelPtr[(i + 1) * img.cols * cn + j * cn + 2];
            //down green
            uint8_t down_g = pixelPtr[(i + 1) * img.cols * cn + j * cn + 1];
            //down blue
            uint8_t down_b = pixelPtr[(i + 1) * img.cols * cn + j * cn + 0];

            //get the average of the neighbors
            uint8_t avg_r = (r + left_r + right_r + up_r + down_r) / 5;
            uint8_t avg_g = (g + left_g + right_g + up_g + down_g) / 5;
            uint8_t avg_b = (b + left_b + right_b + up_b + down_b) / 5;

            //print average pixel
            //cout << "Average pixel: " << unsigned(avg[0]) << " " << unsigned(avg[1]) << " " << unsigned(avg[2]) << endl;

            //update the pixel
            pixelPtr[i * img.cols * cn + j * cn + 0] = avg_b; //B
            pixelPtr[i * img.cols * cn + j * cn + 1] = avg_g; //G
            pixelPtr[i * img.cols * cn + j * cn + 2] = avg_r; //R
        }
    }

    fprintf(stdout, "Writting the output image of size %dx%d...\n", img.rows, img.cols);

    imwrite("../res/jacobi_res.jpg", image_pad);
    imwrite("../res/noised_res.jpg", mColorNoise);
    return 0;
}
