#include "colourmodel_rgb.h"

//constrcutor
ColourModel_RGB::ColourModel_RGB(){

}

//copy constructor
ColourModel_RGB::ColourModel_RGB(int r, int g, int b)
{
    Red = r;
    Green = g;
    Blue = b;
}

//desctructor
ColourModel_RGB::~ColourModel_RGB(){

}

//equals function
bool ColourModel_RGB::Equals(ColourModel_RGB *rgb){
    return (Red == rgb->Red) && (Green == rgb->Green) && (Blue == rgb->Blue);
}

int ColourModel_RGB::getRed(){
    return Red;
}

int ColourModel_RGB::getGreen(){
    return Green;
}

int ColourModel_RGB::getBlue(){
    return Blue;
}

void ColourModel_RGB::setRed(int r){
    Red = r;
}

void ColourModel_RGB::setGreen(int g){
    Green = g;
}

void ColourModel_RGB::setBlue(int b){
    Blue = b;
}
