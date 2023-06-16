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
    int r = (int)rgb->Red;
    int g = (int)rgb->Green;
    int b = (int)rgb->Blue;

    double doubleR = (double)(0);
    double doubleG = (double)(0);
    double doubleB = (double)(0);

    doubleR = (double)(r / 255);
    doubleG = (double)(g / 255);
    doubleB = (double)(b / 255);

    double c = 0;
    double m = 0;
    double y = 0;

    double k = 1 - MaxVal(MaxVal(doubleR, doubleG), doubleB);

    if(k != 1){
        c = (1 - doubleR - k)/(1 - k);
        m = (1 - doubleG - k)/(1 - k);
        y = (1 - doubleB - k)/(1 - k);
    }

    return ColourModel_CMYK(c, m, y , k );

}

ColourModel_CMY ColorConversion::RGBtoCMY(ColourModel_RGB* rgb)
{
    int r = (int)rgb->Red;
    int g = (int)rgb->Green;
    int b = (int)rgb->Blue;

    double doubleR = (double)(0);
    double doubleG = (double)(0);
    double doubleB = (double)(0);

    doubleR = (double)(r / 255);
    doubleG = (double)(g / 255);
    doubleB = (double)(b / 255);

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

    if(doubleR == 0 && doubleG == 0 && doubleB == 0){
        h = 0;
        s = 0;
        i = 0;
        return ColourModel_HSI(h, s, i);
    }

    double doubleRGB = (doubleR + doubleG + doubleB);

    i = doubleRGB / 3;

    double min = MinVal(doubleR, MinVal(doubleG, doubleB));

    s = 1 - 3*(min / doubleRGB);

    if(s < 0.00001)
    {
        s = 0;
    }
    else if(s > 0.99999)
    {
        s = 1;
    }

    if(s != 0)
    {
        h = 0.5 * ((doubleR - doubleG) + (doubleR - doubleB)) / sqrt(((doubleR - doubleG) * (doubleR - doubleG) + (doubleR - doubleB) * (doubleG - doubleB)));
        h = acos(h);

        if(doubleB <= doubleG)
        {
            h = h;
        }
        else
        {
            h = ((360 * 3.14159265) / 180.0) - h;
        }
    }

    h = (h * 180) / 3.14159265;
    s = s*100;
    i = i;


    return ColourModel_HSI(h, s, i);
}

ColourModel_RGB ColorConversion::CMYtoRGB(ColourModel_CMY* cmy)
{
    double r = (double)(0);
    double g = (double)(0);
    double b = (double)(0);

    double c = (double)(cmy->Cyan);
    double m = (double)(cmy->Magenta);
    double y = (double)(cmy->Yellow);

    r = (double)(255 * (1 - c));
    g = (double)(255 * (1 - m));
    b = (double)(255 * (1 - y));

    return ColourModel_RGB(r, g, b);
}

ColourModel_RGB ColorConversion::CMYKtoRGB(ColourModel_CMYK* cmyk)
{
    double r = (double)(0);
    double g = (double)(0);
    double b = (double)(0);

    double c = (double)(cmyk->Cyan);
    double m = (double)(cmyk->Magenta);
    double y = (double)(cmyk->Yellow);
    double k = (double)(cmyk->Black);

    r = (double)(255 * (1 - c) * (1 - k));
    g = (double)(255 * (1 - m) * (1 - k));
    b = (double)(255 * (1 - y) * (1 - k));

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

    if((h >= 0) && (h <= 120))
    {
        r = (int) ((1 + ((s * cos(h)) / cos(60-h))) / 3);
        b = (int) ((1 - s) / 3);
        g = (int) (1 - (r + b));
    }
    else if ((h >= 120) && (h <= 240))
    {
        r = (int) ((1 - s) / 3);
        g = (int) ((1 + ((s * cos(h)) / cos(60 - h))) / 3);
        b = (int) (1 - (r + g));
    }
    else if ((h >= 240) && (h <= 360))
    {
       g = (int) ((1 -  s) / 3);
       b = (int) ((1 + ((s * cos(h)) / cos(60 - h))) / 3);
       r = (int) (1 - (g + b));
    }

    return ColourModel_RGB(r, g, b);

}




