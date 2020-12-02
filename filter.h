#pragma once
#ifndef FILTER_H
#define FILTER_H

#include "config_reader.h"
#include "png_toolkit.h"
#include <vector>
#include <algorithm>
#include "additionals.h"


class filter {
protected:
    rect_t filterArea;
    bool isVerticalPixelExist(image_data &image, int i, rect_t const &filterArea);
    bool isHorizontalPixelExist(image_data &image, int i,  rect_t const &filterArea);
    int getPixelIndex(image_data image, int i, int j);
    unsigned char findIntensity(image_data & image, int index);
    

public:
    void print(image_data &image);
    filter(rect_t &area);
    ~filter();
    virtual void apply_filter(image_data &image) = 0;
};



class convolution_filter :public filter {
protected:
    int weightsSum;
    std::vector<std::vector<int>> filterMatrix;

    void checkRange(int * sum);
    int findConvolusion(image_data & image, int i, int j, int channel);
    void applyConvolusion(image_data &image);
public:
    convolution_filter(rect_t &area);
};




#endif // !FILTER_H

