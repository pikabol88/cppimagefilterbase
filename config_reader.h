#pragma once
#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "additionals.h"

class config_reader {

    typedef struct configData_t {
        std::string filterName;
        rect_t coordinates;
    }configData_t;

private:
    std::string filePath;
    std::ifstream stream;
    std::vector<configData_t*>data;
    std::string filterName;
    rect_t coordinates;

public:

    int count = 0;
    config_reader(std::string path);
    ~config_reader();

    int parseConfig();
    void setData(std::string filterName, rect_t rect);
    void setCoordinates(rect_t rect);
    void setFilterName(std::string filter);
    rect_t getCoordinates();
    std::string getFilterName();
};
#endif // !CONFIG_READER