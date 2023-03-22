#ifndef COLOURMODEL_RGB_H
#define COLOURMODEL_RGB_H

#include <QDebug>
#include "icolourmodel.h"
#include "colorconversion.h"

class ColourModel_RGB /*: public IColourModel*/
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

protected:
    int Red;
    int Green;
    int Blue;

    friend class ColorConversion;
};

#endif // COLOURMODEL_RGB_H
