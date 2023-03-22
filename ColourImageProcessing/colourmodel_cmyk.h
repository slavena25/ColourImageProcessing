#ifndef COLOURMODEL_CMYK_H
#define COLOURMODEL_CMYK_H

#include "colorconversion.h"

class ColourModel_CMYK
{
public:
    ColourModel_CMYK();
    ColourModel_CMYK(double c, double m, double y, double k);
    ~ColourModel_CMYK();

    bool Equals(ColourModel_CMYK *cmyk);

    //getters
    double getCyan();
    double getMagenta();
    double getYellow();
    double getBlack();

    //setters
    void setCyan(double c);
    void setMagenta(double m);
    void setYellow(double y);
    void setBlack(double k);

protected:
    double Cyan;
    double Magenta;
    double Yellow;
    double Black;

    friend class ColorConversion;
};

#endif // COLOURMODEL_CMYK_H
