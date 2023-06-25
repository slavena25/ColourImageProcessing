#ifndef COLOURMODEL_CMY_H
#define COLOURMODEL_CMY_H

#include "colorconversion.h"

class ColourModel_CMY
{
public:
    ColourModel_CMY();
    ColourModel_CMY(double c, double m, double y);
    ~ColourModel_CMY();

    bool Equals(ColourModel_CMY *cmy);

    //getters
    double getCyan();
    double getMagenta();
    double getYellow();

    //setters
    void setCyan(double c);
    void setMagenta(double m);
    void setYellow(double y);

private:
    double Cyan;
    double Magenta;
    double Yellow;

    friend class ColorConversion;
};

#endif // COLOURMODEL_CMY_H
