#ifndef COLORCONVERSION_H
#define COLORCONVERSION_H

#include <cmath>
#include "colourmodel_rgb.h"
#include "colourmodel_cmy.h"
#include "colourmodel_cmyk.h"
#include "colourmodel_hsi.h"

//doesn't work, has to be fixed;
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
    ColourModel_RGB RGB;
    ColourModel_CMY CMY;
    ColourModel_CMYK CMYK;
    ColourModel_HSI HSI;

    //conversion model-to-model
    CMYK RGBtoCMYK(ColourModel_RGB* rgb);
    CMY RGBtoCMY(ColourModel_RGB* rgb);
    HSI RGBtoHSI(ColourModel_RGB* rgb);
    RGB CMYtoRGB(ColourModel_CMY* cmy);
    RGB CMYKtoRGB(ColourModel_CMYK* cmyk);
    RGB HSItoRGB(ColourModel_HSI* hsi);

    //conversion
    void convertToCMY(ColourModel_CMY* cmy, ColourModel_RGB* rgb);
    void convertToCMYK(ColourModel_CMYK* cmyk, ColourModel_RGB);
    void convertToHSI(ColourModel_HSI* hsi, ColourModel_RGB* rgb);

};


#endif // COLORCONVERSION_H
