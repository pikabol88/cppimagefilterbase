#pragma once
#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <string>
#include <fstream>
#include <iostream>

#include "additionals.h"

class config_reader {

private: 
    std::string filePath;
    std::ifstream stream;
    std::string filterName;
    rect_t coordinates;

public:    
    
    config_reader(std::string path);
    ~config_reader();

    void parseConfig();
    void setCoordinates(rect_t rect);
    void setFilterName(std::string filter);
    rect_t getCoordinates();
    std::string getFilterName(); 
};
#endif // !CONFIG_READER
