#ifndef SPECIALSHAPEONE_H
#define SPECIALSHAPEONE_H

#include "Shape.h"

class SpecialShapeOne
        : public Shape
{
public:
    SpecialShapeOne(int p1, int p2);

    virtual ~SpecialShapeOne();

protected:
    void computeTriangles();

};

#endif // SPECIALSHAPEONE_H
