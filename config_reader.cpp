#include "config_reader.h"
#include <string>

config_reader::config_reader(std::string path) : filePath(path), stream(path) {
    while (stream.peek() != EOF) {
        parseConfig();
    }
}

config_reader::~config_reader() {
    stream.close();
    for (int i = 0;i < data.size();i++) {
        delete data[i];
    }
}

int config_reader::parseConfig() {
    std::string filter;
    stream >> filter;
    rect_t rect;
    stream >> rect.up >> rect.left >> rect.bottom >> rect.right;
    setData(filter, rect);
    return 0;
}

void config_reader::setData(std::string filterName, rect_t rect) {
    if (filterName == "") {
        return;
    }
    configData_t *newData = new configData_t;
    newData->coordinates = rect;
    newData->filterName = filterName;
    data.push_back(newData);
    count++;
}


void config_reader::setCoordinates(rect_t rect) {
    coordinates = rect;
}

void config_reader::setFilterName(std::string filter) {
    filterName = filter;
}

rect_t config_reader::getCoordinates() {
    int index = data.size() - count - 1;
    return data[index]->coordinates;
}

std::string config_reader::getFilterName() {
    int index = data.size() - count - 1;
    return data[index]->filterName;
}
