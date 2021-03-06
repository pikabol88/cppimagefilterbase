#include "filter_types.h"


red_filter::red_filter(rect_t &area) : filter(area) { }

void red_filter::apply_filter(image_data &image) {
    for (int i = filterArea.up; i < filterArea.bottom;i++) {
        for (int j = filterArea.left;j < filterArea.right;j++) {
            int index = getPixelIndex(image, i, j);
            image.pixels[index] = 255;
            image.pixels[index + 1] = 0;
            image.pixels[index + 2] = 0;
        }
    }
}



black_white_filter::black_white_filter(rect_t & area) :filter(area) {}

void black_white_filter::apply_filter(image_data & image) {
    for (int i = filterArea.up; i < filterArea.bottom;i++) {
        for (int j = filterArea.left;j < filterArea.right;j++) {
            int index = getPixelIndex(image, i, j);
            unsigned char intensity = findIntensity(image, index);
            image.pixels[index] = image.pixels[index + 1] = image.pixels[index + 2] = intensity;
        }
    }
}

threshold_filter::threshold_filter(rect_t & area) :filter(area) {
    bw_filter = new black_white_filter(area);
}

threshold_filter::~threshold_filter() {
    delete bw_filter;
    bw_filter = nullptr;
}


void threshold_filter::apply_filter(image_data & image) {
    bw_filter->apply_filter(image);
    std::vector<int>pixelsToZero;
    for (int i = filterArea.up; i < filterArea.bottom;i++) {
        for (int j = filterArea.left;j < filterArea.right;j++) {
            int index = getPixelIndex(image, i, j);
            int median = findMedian(image, i, j);
            if (findIntensity(image, index) < median) {
                pixelsToZero.push_back(index);
            }
        }
    }
    for (int index : pixelsToZero) {
        image.pixels[index] = image.pixels[index + 1] = image.pixels[index + 2] = 0;
    }
}

int threshold_filter::findMedian(image_data &image, int i, int j) {
    std::vector<stbi_uc>pixelsIntensity;
    int x = i - 2;
    int y = j - 2;
    for (int ii = 0; ii < 5; ii++) {
        if (isVerticalPixelExist(image, x + ii, filterArea)) {
            for (int jj = 0; jj < 5; jj++) {
                if (isHorizontalPixelExist(image, y + jj, filterArea)) {
                    int index = getPixelIndex(image, x + ii, y + jj);
                    pixelsIntensity.push_back(findIntensity(image, index));
                }
            }
        }
    }
    nth_element(pixelsIntensity.begin(), pixelsIntensity.begin() + pixelsIntensity.size() / 2, pixelsIntensity.end());
    int size = pixelsIntensity.size();
    /*if (size % 2 == 1) {
        return pixelsIntensity[size / 2];
    }
    else {
        return int(0.5*(pixelsIntensity[size / 2 - 1] + pixelsIntensity[size / 2]));
    }*/
    return pixelsIntensity[size / 2];
}




edge_filter::edge_filter(rect_t & area) :convolution_filter(area) {
    bw_filter = new black_white_filter(area);
    filterMatrix.resize(3);
    for (int i = 0, size = filterMatrix.size(); i < size; i++) {
        filterMatrix[i].resize(3);
        for (int j = 0, size2 = filterMatrix[i].size(); j < size2; j++) {
            filterMatrix[i][j] = -1;
            weightsSum += filterMatrix[i][j];
        }
    }
    filterMatrix[1][1] = 9;
    weightsSum += filterMatrix[1][1] + 1;
}

edge_filter::~edge_filter() {
    delete bw_filter;
    bw_filter = nullptr;
}

void edge_filter::apply_filter(image_data & image) {
    bw_filter->apply_filter(image);
    applyConvolusion(image);
}



blur_filter::blur_filter(rect_t & area) :convolution_filter(area) {
    filterMatrix.resize(3);
    for (int i = 0, size = filterMatrix.size(); i < size; i++) {
        filterMatrix[i].resize(3);
        for (int j = 0, size2 = filterMatrix[i].size(); j < size2; j++) {
            filterMatrix[i][j] = 1;
            weightsSum += filterMatrix[i][j];
        }
    }
}

void blur_filter::apply_filter(image_data & image) {
    applyConvolusion(image);
}