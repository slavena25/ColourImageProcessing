#ifndef COLOURMODEL_HSI_H
#define COLOURMODEL_HSI_H

#include "colorconversion.h"

class ColourModel_HSI
{
public:
    ColourModel_HSI();
    ColourModel_HSI(double h, double s, double i);
    ~ColourModel_HSI();

    bool Equals(ColourModel_HSI* hsi);

    //getters
    double getHue();
    double getSaturation();
    double getIntensity();

    //setters
    void setHue(int h);
    void setSaturation(int s);
    void setIntensity(int i);

protected:
    double Hue;
    double Saturation;
    double Intensity;

    friend class ColorConversion;
};

#endif // COLOURMODEL_HSI_H
