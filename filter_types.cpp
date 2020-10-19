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
            int intensity = findIntensity(image, index);
            image.pixels[index] = intensity;
            image.pixels[index + 1] = intensity;
            image.pixels[index + 2] = intensity;

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
  //  image_data imageCopy = image.copy();
    std::vector<stbi_uc*>pixels;
    for (int i = filterArea.up; i < filterArea.bottom;i++) {
        for (int j = filterArea.left;j < filterArea.right;j++) {
            int index = getPixelIndex(image, i, j);           
            int median = findMedian(image, i, j);           
          //  int median = findMedian(imageCopy, i, j);
            if (findIntensity(image, index) < median) {
                pixels.push_back(&(image.pixels[index]));
                /*image.pixels[index] = 0;
                image.pixels[index + 1] = 0;
                image.pixels[index + 2] = 0;*/
            }
        }
    }
    int length = pixels.size();
    for (int i = 0;i < length;i++) {
        *pixels[i] = *(pixels[i]+1) = *(pixels[i] + 2) = 0;
    }
    pixels.clear();
    //imageCopy.deleteCopy();
}

int threshold_filter::findMedian(image_data &image, int i, int j) {
    std::vector<stbi_uc>pixelsIntensity;
    int x = i - 2;
    int y = j - 2;
    for (int ii = 0;ii < 5;ii++) {
        for (int jj = 0;jj < 5;jj++) {
            if (isPixelExist(image, x + ii, y + jj)) {
                int index = getPixelIndex(image, x + ii, y + jj);
                pixelsIntensity.push_back(findIntensity(image, index));
            }
        }
    }
    std::sort(pixelsIntensity.begin(), pixelsIntensity.end());
    int size = pixelsIntensity.size();
    if (size % 2 == 1) {
        return pixelsIntensity[size / 2];
    }
    else {
        return int(0.5*(pixelsIntensity[size / 2 - 1] + pixelsIntensity[size / 2]));
    }
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