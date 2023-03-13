#include "colorconversion.h"

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
    int r = (int)(255 * (cmy.C - 1));
    int g = (int)(255 * (cmy.M - 1));
    int b = (int)(255 * (cmy.Y - 1));

    return RGB(r, g, b);
}

static RGB CMYKtoRGB(CMYK cmyk)
{
    int r = (int)(255 * (1 - cmyk.C) * (1 - cmyk.K));
    int g = (int)(255 * (1 - cmyk.M) * (1 - cmyk.K));
    int b = (int)(255 * (1 - cmyk.Y) * (1 - cmyk.K));

    return RGB(r, g, b);
}

static RGB HSItoRGB(HSI hsi)
{
    int r = (int)(0);
    int g = (int)(0);
    int b = (int)(0);

    int h = (int)(hsi.H);
    int s = (int)(hsi.S);
    int i = (int)(hsi.I);

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

    return RGB(r, g, b);

}

static convertToCMY(CMY cmy, RGB rgb)
{
    RGBtoCMY(rgb);
    CMYtoRGB(cmy);
}

static convertToCMYK(CMYK cmyk, RGB rgb)
{
    RGBtoCMYK(rgb);
    CMYKtoRGB(cmyk);
}

static convertToHSI(HSI hsi, RGB rgb)
{
    RGBtoHSI(rgb);
    HSItoRGB(hsi);
}



