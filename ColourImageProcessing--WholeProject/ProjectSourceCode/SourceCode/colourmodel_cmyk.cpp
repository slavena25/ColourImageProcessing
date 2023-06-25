#include "colourmodel_cmyk.h"

ColourModel_CMYK::ColourModel_CMYK()
{

}

ColourModel_CMYK::ColourModel_CMYK(double c, double m, double y, double k)
{
    Cyan = c;
    Magenta = m;
    Yellow = y;
    Black = k;
}

ColourModel_CMYK::~ColourModel_CMYK(){

}

bool ColourModel_CMYK::Equals(ColourModel_CMYK *cmyk){
    return (Cyan == cmyk->Cyan) && (Magenta == cmyk->Magenta) && (Yellow == cmyk->Yellow) && (Black == cmyk->Black);
}

double ColourModel_CMYK::getCyan(){
    return Cyan;
}

double ColourModel_CMYK::getMagenta(){
    return Magenta;
}

double ColourModel_CMYK::getYellow(){
    return Yellow;
}

double ColourModel_CMYK::getBlack(){
    return Black;
}

void ColourModel_CMYK::setCyan(double c){
    Cyan = c;
}

void ColourModel_CMYK::setMagenta(double m){
    Magenta = m;
}

void ColourModel_CMYK::setYellow(double y){
    Yellow = y;
}

void ColourModel_CMYK::setBlack(double k){
    Black = k;
}
