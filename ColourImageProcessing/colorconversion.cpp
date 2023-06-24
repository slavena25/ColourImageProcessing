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

        //Lower the values with Channel% of Channel
        //so we can see a change in the picture and have a acurate histogram with the new color
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

    //Lower the values with Channel% of Channel
    //so we can see a change in the picture and have a acurate histogram with the new color
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
    double _RGB = (_red + _green + _blue);

    double rn = _red / _RGB;
    double gn = _green / _RGB;
    double bn = _blue / _RGB;

    i = _RGB / 3 / 255;

    //get the saturation
    double min = MinVal(rn, MinVal(gn, bn));
    s = 1 - (3 * min);

    double a = rn - gn;
    double b = rn - bn;
    double c = gn - bn;

    //Calculate Theta to get the Hue value
    h = 0.5 * (a + b) / (sqrt((qPow(a, 2) + (b * c))) + 0.000001);
    h = qAcos(h);

    if(bn > gn)
    {
        h = (2 * M_PI) - h;
    }

    h = qRound((h * 180 / M_PI));
    s = qRound(s * 100);
    i = i * 255;

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

ColourModel_RGB ColorConversion::HSItoRGB(ColourModel_HSI* hsi){

    double r = 0;
    double g = 0;
    double b = 0;

    double h = hsi->getHue() * M_PI / 180;
    double s = hsi->getSaturation() / 100;
    double i = hsi->getIntensity() / 255;

    double x = i * (1-s);
    double y = i * (1 + ((s*qCos(h))/qCos(M_PI / 3 - h)));
    double z = 3 * i - (x + y);

    if(h < 2 * M_PI / 3){
        b = x;
        r = y;
        g = z;
    }else if(2 * M_PI / 3 <= h && h < 4 * M_PI/3){
        h = h - 2 * M_PI / 3;
        r = x;
        g = y;
        b = z;

    }else if(4 * M_PI / 3 <= h && h < 2*M_PI){
        h = h - 4 * M_PI / 3;
        g = x;
        b = y;
        r = z;

    }

    r = qRound(r * 255);
    g = qRound(g * 255);
    b = qRound(b * 255);

    return ColourModel_RGB(r,g,b);

}

