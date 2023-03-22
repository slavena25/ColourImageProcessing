#include "colourmodel_hsi.h"

//constructor
ColourModel_HSI::ColourModel_HSI(){

}

//copy constructor
ColourModel_HSI::ColourModel_HSI(double h, double s, double i){
    Hue = h;
    Saturation = s;
    Intensity = i;

}

//destructor
ColourModel_HSI::~ColourModel_HSI(){

}

//equals
bool ColourModel_HSI::Equals(ColourModel_HSI *hsi){
    return (Hue == hsi->Hue) && (Saturation == hsi->Saturation) && (Intensity == hsi->Intensity);
}

//get Hue value
double ColourModel_HSI::getHue(){
    return Hue;
}

//get Saturation value
double ColourModel_HSI::getSaturation(){
    return Saturation;
}

//get Intensity value
double ColourModel_HSI::getIntensity(){
    return Intensity;
}

//set Hue value
void ColourModel_HSI::setHue(int h){
    Hue = h;
}

//set Saturation value
void ColourModel_HSI::setSaturation(int s){
    Saturation = s;
}

//set Intensity value
void ColourModel_HSI::setIntensity(int i){
    Intensity = i;
}
