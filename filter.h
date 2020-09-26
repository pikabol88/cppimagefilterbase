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
    bool isPixelExist(image_data &image, int i, int j);
    int getPixelIndex(image_data image, int i, int j);
    int findIntensity(image_data & image, int index);
    void print(image_data &image);

public:
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



