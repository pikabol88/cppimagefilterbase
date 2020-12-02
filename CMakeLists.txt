cmake_minimum_required(VERSION 2.8)

project(Filters)
add_executable(${PROJECT_NAME} "main.cpp" "png_toolkit.cpp" "png_toolkit.h"
    "stb_image.h" "stb_image_write.h" "additionals.h" "config_reader.cpp" "config_reader.h" "filter.cpp" "filter.h" "filter_manager.cpp" "filter_manager.h" "filter_types.cpp" "filter_types.h")
