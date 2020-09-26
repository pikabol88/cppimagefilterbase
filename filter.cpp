#include"filter.h"

//for debug process
void filter::print(image_data &image)
{
    std::cout << "\n\n\n\n";
    for (int i = filterArea.up; i < 7;i++) {
        for (int j = filterArea.left;j < 7;j++) {
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

int filter::findIntensity(image_data &image, int index) {
    return int((0.3 * image.pixels[index]) + (0.6 * image.pixels[index + 1]) + (0.1*image.pixels[index + 2]));
}

bool filter::isPixelExist(image_data &image, int i, int j) {
    if (i >= 0 && i < image.h) {
        if (j >= 0 && j < image.w) {
            return true;
        }
    }
    return false;
}




convolution_filter::convolution_filter(rect_t & area): filter(area) {
    weightsSum = 0;
}


void convolution_filter::checkRange(int *sum) {
    if (*sum >= 0) {
        if (*sum >= 256) {
            *sum = 255;
        }
    } else {
        *sum = 0;
    }
}

int convolution_filter::findConvolusion(image_data & image, int i, int j, int channel) {
    int shift = filterMatrix[0].size() / 2;
    int sum = 0;
    for (int ii = 0, size1 = filterMatrix.size(); ii < size1; ii++) {
        for (int jj = 0, size2 = filterMatrix[0].size(); jj < size2; jj++) {
            if (isPixelExist(image, i - shift + ii, j - shift + jj)) {
                int index =  getPixelIndex(image, i - shift + ii, j - shift + jj);
                int comp = image.pixels[index + channel];
                int tmp = filterMatrix[ii][jj] * comp;
                sum += tmp;
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
}


