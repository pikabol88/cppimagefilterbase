#include "filter_manager.h"
#include <algorithm>


filter_manager::filter_manager(config_reader &config, image_data &image) {
    decideFilterType(config.getFilterName());
    calculateArea(config.getCoordinates(), image);
}



void filter_manager::calculateArea(rect_t rect, image_data &image) {
    applicationArea.up = (rect.up) ? image.h / rect.up : 0;
    applicationArea.right = (rect.right) ? image.w / rect.right : 0;
    applicationArea.bottom = (rect.bottom) ? image.h / rect.bottom : 0;
    applicationArea.left = (rect.left) ? image.w / rect.left : 0;
}
bool search_substring(std::string str, std::string substring) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    size_t pos = str.find(substring);
    if (pos != std::string::npos)
        return true;
    return false;
}

void filter_manager::decideFilterType(std::string name) {
    if (search_substring(name, "red")) {
        type = RED_FILTER;
    }
    else if (search_substring(name, "bw")|| search_substring(name, "blackandwhite")) {
        type = BLACK_WHITE_FILTER;
    }
    else if (search_substring(name, "threshold")) {
        //type = THRESHOLD_FILTER;
       
    }
    else if (search_substring(name, "edge")) {
        type = EDGE_FILTER;
    }
    else if (search_substring(name, "blur")) {
        type = BLUR_FILTER;
    }
}

filter * filter_manager::getFilter() {
    filter *filter;
    switch (type)
    {
    case RED_FILTER:
        filter = new red_filter(applicationArea);
        return filter;
    case BLACK_WHITE_FILTER:
        filter = new black_white_filter(applicationArea);
        return filter;
    case THRESHOLD_FILTER:
        filter = new threshold_filter(applicationArea);
        return filter;
    case BLUR_FILTER:
        filter = new blur_filter(applicationArea);
        return filter;
    case EDGE_FILTER:
        filter = new edge_filter(applicationArea);
        return filter;
    default:
        break;
    }
    return nullptr;
}
