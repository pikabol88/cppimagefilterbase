#ifndef PNG_TOOLKIT_H
#define PNG_TOOLKIT_H

#include <string>
#include <map>
#include "stb_image.h"

struct image_data
{
    stbi_uc *pixels;
    int w, h;
    int compPerPixel;

    image_data copy() {
        image_data new_image;
        new_image.h = h;
        new_image.w = w;
        new_image.compPerPixel = compPerPixel;
        int img_size = w * h * compPerPixel;
        new_image.pixels = new stbi_uc[img_size];
        for (int i = 0;i < img_size;i++) {
            new_image.pixels[i] = pixels[i];
        }
        return new_image;
    }

    void deleteCopy() {
        delete pixels;
    }
};

class png_toolkit {
public:
    enum class Error {
        WrongSize,
        WrongFormat,
        Ok
    };
    png_toolkit();
    ~png_toolkit();
    bool load(std::string const &pictureName);
    bool save(std::string const &pictureName);
    image_data getPixelData(void) const;


private:
    image_data imgData;
};

#endif // PNG_TOOLKIT_H