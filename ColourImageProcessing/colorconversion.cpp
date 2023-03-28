#include "colorconversion.h"

ColorConversion::ColorConversion(){

}

double ColorConversion::MaxVal(double a, double b)
{
    return a >= b ? a : b;
}

double ColorConversion::MinVal(double a, double b)
{
    return a >= b ? b : a;
}

ColourModel_CMYK ColorConversion::RGBtoCMYK(ColourModel_RGB* rgb)
{
    double doubleR = (double)rgb->Red / 255;
    double doubleG = (double)rgb->Green / 255;
    double doubleB = (double)rgb->Blue / 255;

    double k = 1 - MaxVal(MaxVal(doubleR, doubleG), doubleB);
    double c = (1 - doubleR - k)/(1 - k);
    double m = (1 - doubleG - k)/(1 - k);
    double y = (1 - doubleB - k)/(1 - k);

    return ColourModel_CMYK(c, m, y , k );

}

ColourModel_CMY ColorConversion::RGBtoCMY(ColourModel_RGB* rgb)
{
    double doubleR = (double)rgb->Red / 255;
    double doubleG = (double)rgb->Green / 255;
    double doubleB = (double)rgb->Blue / 255;

    double c = 1 - doubleR;
    double m = 1 - doubleG;
    double y = 1 - doubleB;

    return ColourModel_CMY(c, m, y);

}

ColourModel_HSI ColorConversion::RGBtoHSI(ColourModel_RGB* rgb)
{
    double doubleR = (double)rgb->Red;
    double doubleG = (double)rgb->Green;
    double doubleB = (double)rgb->Blue;

    double h;
    double s;
    double i;

    double doubleRGB = (doubleR + doubleG + doubleB);

    i = doubleRGB / 3;

    if(doubleRGB == 765)
    {
        s = 0;
        h = 0;
    }

    if(i > 0)
    {
        s = 1 - MinVal(doubleR, MinVal(doubleG, doubleB));
    }
    else if(i == 0)
    {
        s = 0;
    }

    if(doubleG >= doubleB)
    {
        h = 360 - acos(doubleR - (doubleG / 2) - (doubleB / 2) / sqrt((doubleR * doubleR) + (doubleG * doubleG) + (doubleB*doubleB) - (doubleR * doubleG) - (doubleR * doubleB) - (doubleG * doubleB)));
    }

    return ColourModel_HSI(h, s, i);
}

ColourModel_RGB ColorConversion::CMYtoRGB(ColourModel_CMY* cmy)
{
    int r = (int)(255 * (cmy->Cyan - 1));
    int g = (int)(255 * (cmy->Magenta - 1));
    int b = (int)(255 * (cmy->Yellow - 1));

    return ColourModel_RGB(r, g, b);
}

ColourModel_RGB ColorConversion::CMYKtoRGB(ColourModel_CMYK* cmyk)
{
    int r = (int)(255 * (1 - cmyk->Cyan) * (1 - cmyk->Black));
    int g = (int)(255 * (1 - cmyk->Magenta) * (1 - cmyk->Black));
    int b = (int)(255 * (1 - cmyk->Yellow) * (1 - cmyk->Black));

    return ColourModel_RGB(r, g, b);
}

ColourModel_RGB ColorConversion::HSItoRGB(ColourModel_HSI* hsi)
{
    int r = (int)(0);
    int g = (int)(0);
    int b = (int)(0);

    int h = (int)(hsi->Hue);
    int s = (int)(hsi->Saturation);
    int i = (int)(hsi->Intensity);

    if(h == 0)
    {
        r = (int) (i + (2 * i * s));
        g = (int) (i - ( i + s));
        b = (int) (i - ( i * s));
    }
    else if((h > 0) && (h < 120))
    {
        r = (int) (i + (i * s) * cos(h) / cos(60-h));
        g = (int) (i + (i * s) * (1 - cos(h) / cos(60-h)));
        b = (int) (i - (i * s));
    }
    else if(h == 120)
    {
        r = (int) (i - (i * s));
        g = (int) (i + (2 * i * s));
        b = (int) (i - (i * s));
    }
    else if ((h > 120) && (h < 240))
    {
        r = (int) (i - (i * s));
        g = (int) (i + (i * s) * cos(h-120) / cos(180-h));
        b = (int) (i + (i * s) * (1 - cos(h-120) / cos(180-h)));
    }
    else if (h == 240)
    {
       r = (int) (i - (i * s));
       g = (int) (i - (i * s));
       b = (int) (i + (2 * i * s));
    }
    else if ((h > 240) && (h < 360))
    {
       r = (int) (i + (i * s) * (1 - cos(h-240) / cos(300-h)));
       g = (int) (i - (i * s));
       b = (int) (i + (i * s) * cos(h-240) / cos(300-h));
    }

    return ColourModel_RGB(r, g, b);

}




