#ifndef COLORCONVERSION_H
#define COLORCONVERSION_H

#include "colourmodel_rgb.h"
#include "colourmodel_cmy.h"
#include "colourmodel_cmyk.h"
#include "colourmodel_hsi.h"


class ColourModel_RGB;
class ColourModel_CMY;
class ColourModel_CMYK;
class ColourModel_HSI;

class ColorConversion
{
public:
    ColorConversion();
    ~ColorConversion();

    //max-min functions
    double MaxVal(double a, double b);
    double MinVal(double a, double b);

    //colour model constructors
    //ERROR --> not inialized
    ColourModel_RGB* RGB;
    ColourModel_CMY* CMY;
    ColourModel_CMYK* CMYK;
    ColourModel_HSI* HSI;

    //conversion model-to-model
    ColourModel_CMYK RGBtoCMYK(ColourModel_RGB* rgb);
    ColourModel_CMY RGBtoCMY(ColourModel_RGB* rgb);
    ColourModel_HSI RGBtoHSI(ColourModel_RGB* rgb);
    ColourModel_RGB CMYtoRGB(ColourModel_CMY* cmy);
    ColourModel_RGB CMYKtoRGB(ColourModel_CMYK* cmyk);
    ColourModel_RGB HSItoRGB(ColourModel_HSI* hsi);

    //conversion
    void convertToCMY(ColourModel_CMY* cmy, ColourModel_RGB* rgb);
    void convertToCMYK(ColourModel_CMYK* cmyk, ColourModel_RGB* rgb);
    void convertToHSI(ColourModel_HSI* hsi, ColourModel_RGB* rgb);


};


#endif // COLORCONVERSION_H
