#include"filter.h"

//for debug process
void filter::print(image_data &image)
{
    std::cout << "\n\n\n\n";
    for (int i = filterArea.up; i < filterArea.bottom;i++) {
        for (int j = filterArea.left;j < filterArea.right;j++) {
            std::cout << "pix[" << i << "][" << j << "]:";
            int index = getPixelIndex(image, i, j);
            std::cout << "(r:" << int(image.pixels[index]);
            std::cout << ",g:" << int(image.pixels[index + 1]);
            std::cout << ",b:" << int(image.pixels[index + 2]) << ") ";
        }
        std::cout << "\n";
    }
}

filter::filter(rect_t &area) : filterArea(area) {}
filter::~filter() {}

int filter::getPixelIndex(image_data image, int i, int j) {
    return (i * image.w + j)*image.compPerPixel;
}

unsigned char filter::findIntensity(image_data &image, int index) {
    int intensity = ((3 * image.pixels[index]) + (6 * image.pixels[index + 1]) + (1 * image.pixels[index + 2])) / 10;
    return (unsigned char)intensity;
}

bool filter::isVerticalPixelExist(image_data &image, int i, rect_t const &filterArea) {
    if (i >= filterArea.up && i < filterArea.bottom) {
        return true;
    }
    return false;
}

bool filter::isHorizontalPixelExist(image_data &image, int i, rect_t const &filterArea) {

    if (i >= filterArea.left && i < filterArea.right) {
        return true;
    }
    return false;
}

convolution_filter::convolution_filter(rect_t & area) : filter(area) {
    weightsSum = 0;
}


void convolution_filter::checkRange(int *sum) {
    if (*sum >= 0) {
        if (*sum >= 256) {
            *sum = 255;
        }
    }
    else {
        *sum = 0;
    }
}

int convolution_filter::findConvolusion(image_data & image, int i, int j, int channel) {
    int shift = filterMatrix[0].size() / 2;
    int sum = 0;
    for (int ii = 0, size1 = filterMatrix.size(); ii < size1; ii++) {
        if (isVerticalPixelExist(image, i - shift + ii, filterArea)) {
            for (int jj = 0, size2 = filterMatrix[0].size(); jj < size2; jj++) {
                if (isHorizontalPixelExist(image, j - shift + jj, filterArea)) {
                    int index = getPixelIndex(image, i - shift + ii, j - shift + jj);
                    int comp = image.pixels[index + channel];
                    int tmp = filterMatrix[ii][jj] * comp;
                    sum += tmp;
                }
            }
        }
    }
    sum = sum / weightsSum;
    checkRange(&sum);
    return sum;
}

void convolution_filter::applyConvolusion(image_data & image) {
    image_data imageCopy = image.copy();
    for (int i = filterArea.up; i < filterArea.bottom;i++) {
        for (int j = filterArea.left;j < filterArea.right;j++) {
            int index = getPixelIndex(image, i, j);
            for (int channel = 0;channel < 3;channel++) {
                int convolution = findConvolusion(imageCopy, i, j, channel);
                image.pixels[index + channel] = convolution;
            }
        }
    }
    imageCopy.deleteCopy();
}
