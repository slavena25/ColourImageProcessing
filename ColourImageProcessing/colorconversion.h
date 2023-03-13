#ifndef COLORCONVERSION_H
#define COLORCONVERSION_H

#include <cmath>

class CMYK
{
    public:
        double C;
        double M;
        double Y;
        double K;

        CMYK(double c, double m, double y, double k)
        {
            C = c;
            M = m;
            Y = y;
            K = k;
        }

        bool Equals(CMYK cmyk)
        {
            return (C == cmyk.C) && (M == cmyk.M) && (Y == cmyk.Y) && (K == cmyk.K);
        }

};

class CMY
{
    public:
        double C;
        double M;
        double Y;

        CMY(double c, double m, double y)
        {
            C = c;
            M = m;
            Y = y;
        }

        bool Equals(CMY cmy)
        {
            return (C == cmy.C) && (M == cmy.M) && (Y == cmy.Y);
        }
};

class RGB
{
    public:
        int R;
        int G;
        int B;

        RGB(int r, int g, int b)
        {
            R = r;
            G = g;
            B = b;
        }

        bool Equals(RGB rgb)
        {
            return (R == rgb.R) && (G == rgb.B) && (B == rgb.B);
        }

};

class HSI
{
    public:
        double H;
        double S;
        double I;

        HSI(double h, double s, double i)
        {
            H = h;
            S = s;
            I = i;
        }

        bool Equals(HSI hsi)
        {
            return (H == hsi.H) && (S == hsi.S) && (I == hsi.I);
        }
};

#endif // COLORCONVERSION_H
