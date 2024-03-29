#ifndef COLOURMODEL_RGB_H
#define COLOURMODEL_RGB_H

#include <QDebug>
#include "colorconversion.h"

class ColourModel_RGB
{
public:
    ColourModel_RGB();
    ColourModel_RGB(int r, int g, int b);
    ~ColourModel_RGB();

    bool Equals(ColourModel_RGB* rgb);

    //getters
    int getRed();
    int getGreen();
    int getBlue();

    //setters
    void setRed(int r);
    void setGreen(int g);
    void setBlue(int b);

private:
    double Red;
    double Green;
    double Blue;

    friend class ColorConversion;
};

#endif // COLOURMODEL_RGB_H
