#include "config_reader.h"
#include <string>

config_reader::config_reader(std::string path) : filePath(path), stream(path){
    parseConfig();
}

config_reader::~config_reader() { 
    stream.close();
}

void config_reader::parseConfig() {
    std::string filter;
    stream >> filter;
    setFilterName(filter);
    
    rect_t rect;
    stream >> rect.up >>rect.left>>rect.bottom>>rect.right;
    setCoordinates(rect);    
}


void config_reader::setCoordinates(rect_t rect) {
    coordinates = rect;
}

void config_reader::setFilterName(std::string filter) {
    filterName = filter;
}

rect_t config_reader::getCoordinates() {
    return coordinates;
}

std::string config_reader::getFilterName() {
    return filterName;
}


