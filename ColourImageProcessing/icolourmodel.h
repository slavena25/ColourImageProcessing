#ifndef ICOLOURMODEL_H
#define ICOLOURMODEL_H

//is it needed?
//TO BE IMPLEMENTED
//BASE class for the colour models
class IColourModel
{
public:
    IColourModel();
    IColourModel(int a, int b, int c);
    virtual bool Equals(IColourModel icolourModel) = 0;
};

#endif // ICOLOURMODEL_H
