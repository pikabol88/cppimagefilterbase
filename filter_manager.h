#pragma once
#ifndef FILTER_MANAGER_H
#define FILTER_MANAGER_H

#include "config_reader.h"
#include "filter.h"
#include "filter_types.h"
#include "additionals.h"

class filter_manager {

    typedef enum filter_type {
        RED_FILTER,
        BLACK_WHITE_FILTER,
        THRESHOLD_FILTER,
        BLUR_FILTER,
        EDGE_FILTER
    } filter_type_t;

    filter_type_t type;
    rect_t applicationArea;
    void calculateArea(rect_t rect, image_data &image);
    void decideFilterType(std::string name);
    
public:
    filter_manager(config_reader & config, image_data & image);
    filter* getFilter();
};

#endif // !FILTER_MANAGER


