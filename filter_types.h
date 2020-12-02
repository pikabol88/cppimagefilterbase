#pragma once
#ifndef FILTER_TYPES_H
#define FILTER_TYPES_H

#include"filter.h"

class red_filter :public filter {
public:
    red_filter(rect_t &area);
    virtual void apply_filter(image_data &image) override;
};


class black_white_filter :public filter {
public:
    black_white_filter(rect_t &area);
    virtual void apply_filter(image_data &image) override;
};


class threshold_filter :public filter {
    black_white_filter* bw_filter;
    int findMedian(image_data &image, int i, int j);
public:
    threshold_filter(rect_t &area);
    ~threshold_filter();
    virtual void apply_filter(image_data &image) override;
};


class edge_filter : public convolution_filter {
    black_white_filter* bw_filter;
public:
    edge_filter(rect_t &area);
    ~edge_filter();
    virtual void apply_filter(image_data &image) override;
};


class blur_filter :public convolution_filter {
public:
    blur_filter(rect_t &area);
    virtual void apply_filter(image_data &image) override;
};

#endif // !FILTER_TYPES_H