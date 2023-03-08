#include "colourconversion.h"
#include <cmath>

static double Max(double a, double b)
{
    return a >= b ? a : b;
}

static double Min(double a, double b)
{
    return a >= b ? b : a;
}


static CMYK RGBtoCMYK(RGB rgb)
{
    double doubleR = (double)rgb.R / 255;
    double doubleG = (double)rgb.G / 255;
    double doubleB = (double)rgb.B / 255;

    double k = 1 - Max(Max(doubleR, doubleG), doubleB);
    double c = (1 - doubleR - k)/(1 - k);
    double m = (1 - doubleG - k)/(1 - k);
    double y = (1 - doubleB - k)/(1 - k);

    return CMYK(c, m, y , k );

}

static CMY RGBtoCMY(RGB rgb)
{
    double doubleR = (double)rgb.R / 255;
    double doubleG = (double)rgb.G / 255;
    double doubleB = (double)rgb.B / 255;

    double c = 1 - doubleR;
    double m = 1 - doubleG;
    double y = 1 - doubleB;

    return CMY(c, m, y);

}

//(R - (G/2) - (B/2)) / (sqrt((R*R) + (G*G) + (B*B) - (R*G) - (R*B) - (G*B)))

static HSI RGBtoHSI(RGB rgb)
{
    double doubleR = (double)rgb.R;
    double doubleG = (double)rgb.G;
    double doubleB = (double)rgb.B;

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
        s = 1 - Min(doubleR, Min(doubleG, doubleB));
    }
    else if(i == 0)
    {
        s = 0;
    }

    if(doubleG >= doubleB)
    {
        h = 360 - acos(doubleR - (doubleG / 2) - (doubleB / 2) / sqrt((doubleR * doubleR) + (doubleG * doubleG) + (doubleB*doubleB) - (doubleR * doubleG) - (doubleR * doubleB) - (doubleG * doubleB)));
    }

    return HSI(h, s, i);
}

static RGB CMYtoRGB(CMY cmy)
{
    unsigned char r = (unsigned char)(255 * (cmy.C - 1));
    unsigned char g = (unsigned char)(255 * (cmy.M - 1));
    unsigned char b = (unsigned char)(255 * (cmy.Y - 1));

    return RGB(r, g, b);
}

static RGB CMYKtoRGB(CMYK cmyk)
{
    unsigned char r = (unsigned char)(255 * (1 - cmyk.C) * (1 - cmyk.K));
    unsigned char g = (unsigned char)(255 * (1 - cmyk.M) * (1 - cmyk.K));
    unsigned char b = (unsigned char)(255 * (1 - cmyk.Y) * (1 - cmyk.K));

    return RGB(r, g, b);
}

static RGB HSItoRGB(HSI hsi)
{
    unsigned char r = (unsigned char)(0);
    unsigned char g = (unsigned char)(0);
    unsigned char b = (unsigned char)(0);

    unsigned char h = (unsigned char)(hsi.H);
    unsigned char s = (unsigned char)(hsi.S);
    unsigned char i = (unsigned char)(hsi.I);

    if(h == 0)
    {
        r = (unsigned char) (i + (2 * i * s));
        g = (unsigned char) (i - ( i + s));
        b = (unsigned char) (i - ( i * s));
    }
    else if((h > 0) && (h < 120))
    {
        r = (unsigned char) (i + (i * s) * cos(h) / cos(60-h));
        g = (unsigned char) (i + (i * s) * (1 - cos(h) / cos(60-h)));
        b = (unsigned char) (i - (i * s));
    }
    else if(h == 120)
    {
        r = (unsigned char) (i - (i * s));
        g = (unsigned char) (i + (2 * i * s));
        b = (unsigned char) (i - (i * s));
    }
    else if ((h > 120) && (h < 240))
    {
        r = (unsigned char) (i - (i * s));
        g = (unsigned char) (i + (i * s) * cos(h-120) / cos(180-h));
        b = (unsigned char) (i + (i * s) * (1 - cos(h-120) / cos(180-h)));
    }
    else if (h == 240)
    {
       r = (unsigned char) (i - (i * s));
       g = (unsigned char) (i - (i * s));
       b = (unsigned char) (i + (2 * i * s));
    }
    else if ((240 < h) && (h < 360))
    {
       r = (unsigned char) (i + (i * s) * (1 - cos(h-240) / cos(300-h)));
       g = (unsigned char) (i - (i * s));
       b = (unsigned char) (i + (i * s) * cos(h-240) / cos(300-h));
    }

    return RGB(r, g, b);

}
