#include <iostream>
#include <string>
#include <malloc.h>
#include "png_toolkit.h"
#include "config_reader.h"
#include "filter_manager.h"
#include "filter.h"



int main(int argc, char *argv[]) {
    try {
        if (argc != 4)
            throw "Not enough arguments";
        
        config_reader config(argv[1]);
        png_toolkit studTool;     
        int count = config.count;
        try {
            if (!studTool.load(argv[2]))
                throw "Can't open image";
            image_data image = studTool.getPixelData();
            while(config.count--) {
                filter_manager manager(config, image);
                filter *filter = manager.getFilter();
                if (filter) {
                    filter->apply_filter(image);
                }
                studTool.save(argv[3]);
            }
        } catch (const char *str) {  std::cout << "Error: " << str << std::endl;
          return 1;
        }

    } catch (const char *str) {  std::cout << "Error: " << str << std::endl;
      return 1;
    }

    return 0;
}
