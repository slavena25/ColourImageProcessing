#include "colourmodel_cmy.h"

ColourModel_CMY::ColourModel_CMY(){

}

ColourModel_CMY::ColourModel_CMY(double c, double m, double y)
{
    Cyan = c;
    Magenta = m;
    Yellow = y;
}

ColourModel_CMY::~ColourModel_CMY(){

}

bool ColourModel_CMY::Equals(ColourModel_CMY *cmy){
    return (Cyan == cmy->Cyan) && (Magenta == cmy->Magenta) && (Yellow == cmy->Yellow);
}

double ColourModel_CMY::getCyan(){
    return Cyan;
}

double ColourModel_CMY::getMagenta(){
    return Magenta;
}

double ColourModel_CMY::getYellow(){
    return Yellow;
}

void ColourModel_CMY::setCyan(double c){
    Cyan = c;
}

void ColourModel_CMY::setMagenta(double m){
    Magenta = m;
}

void ColourModel_CMY::setYellow(double y){
    Yellow =y;
}
