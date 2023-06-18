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
    double doubleR = rgb->Red / 255;
    double doubleG = rgb->Green / 255;
    double doubleB = rgb->Blue / 255;

    double c = 1 - doubleR;
    double m = 1 - doubleG;
    double y = 1 - doubleB;

    double k = 1 - MaxVal(MaxVal(doubleR, doubleG), doubleB);

    if(k < 1 && k >= 0){
        c = qRound(((c - k)/(1 - k)) * 100);
        m = qRound(((m - k)/(1 - k)) * 100);
        y = qRound(((y - k)/(1 - k)) * 100);

        c = (c / 100) * c;
        m = (m / 100) * m;
        y = (y / 100) * y;
    }

    k = qRound(k * 100);
    return ColourModel_CMYK(c, m, y , k );
}

ColourModel_CMY ColorConversion::RGBtoCMY(ColourModel_RGB* rgb)
{
    double doubleR = rgb->Red / 255;
    double doubleG = rgb->Green / 255;
    double doubleB = rgb->Blue / 255;

    double c = qRound((1 - doubleR) * 100);
    double m = qRound((1 - doubleG) * 100);
    double y = qRound((1 - doubleB) * 100);

    c = (c / 100) * c;
    m = (m / 100) * m;
    y = (y / 100) * y;

    return ColourModel_CMY(c, m, y);

}

ColourModel_HSI ColorConversion::RGBtoHSI(ColourModel_RGB* rgb)
{
    double _red = rgb->Red;
    double _green = rgb->Green;
    double _blue = rgb->Blue;

    double h;
    double s;
    double i;

    if(_red == 0 && _green == 0 && _blue == 0){
        h = 0;
        s = 0;
        i = 0;
        return ColourModel_HSI(h, s, i);
    }

    //get the intensity
    int _RGB = (_red + _green + _blue);
    i = _RGB / 3;

    //get the saturation
    double min = MinVal(_red, MinVal(_green, _blue));
    s = 1 - 3*(min / _RGB);

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
        double a = _red - _green;
        double b = _red - _blue;
        h = 0.5 * (a + b) / sqrt((qPow(a, 2) + qPow(b, 2)));
        h = acos(h);

        if(_blue > _green)
        {
            h = ((360 * 3.14159265) / 180.0) - h;
        }
    }

    h = qRound((h * 180) / 3.14159265);
    s = qRound(s*100);
    i = i;


    return ColourModel_HSI(h, s, i);
}

ColourModel_RGB ColorConversion::CMYtoRGB(ColourModel_CMY* cmy)
{
    double c = cmy->Cyan;
    double m = cmy->Magenta;
    double y = cmy->Yellow;

    double r = (255 * (100 - c)) / 100;
    double g = (255 * (100 - m)) / 100;
    double b = (255 * (100 - y)) / 100;

    return ColourModel_RGB(r, g, b);
}

ColourModel_RGB ColorConversion::CMYKtoRGB(ColourModel_CMYK* cmyk)
{
    double c = cmyk->Cyan / 100;
    double m = cmyk->Magenta / 100;
    double y = cmyk->Yellow / 100;
    double k = cmyk->Black / 100;

    double r = qRound((255 * (1 - c) * (1 - k)));
    double g = qRound((255 * (1 - m) * (1 - k)));
    double b = qRound((255 * (1 - y) * (1 - k)));

    return ColourModel_RGB(r, g, b);
}

ColourModel_RGB ColorConversion::HSItoRGB(ColourModel_HSI* hsi)
{
    double r;
    double g;
    double b;

    double h = hsi->Hue;
    double s = hsi->Saturation;
    double i = hsi->Intensity;

    if((h >= 0) && (h <= 120))
    {
        r = qRound(((1 + ((s * cos(h)) / cos(60-h))) / 3));
        b = qRound(((1 - s) / 3));
        g = qRound((1 - (r + b)));
    }
    else if ((h >= 120) && (h <= 240))
    {
        r = qRound(((1 - s) / 3));
        g = qRound(((1 + ((s * cos(h)) / cos(60 - h))) / 3));
        b = qRound((1 - (r + g)));
    }
    else if ((h >= 240) && (h <= 360))
    {
       g = qRound(((1 -  s) / 3));
       b = qRound(((1 + ((s * cos(h)) / cos(60 - h))) / 3));
       r = qRound((1 - (g + b)));
    }

    return ColourModel_RGB(r, g, b);

}




