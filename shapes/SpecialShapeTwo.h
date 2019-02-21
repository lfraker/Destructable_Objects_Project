#ifndef SPECIALSHAPETWO_H
#define SPECIALSHAPETWO_H

#include "Shape.h"

class SpecialShapeTwo
        : public Shape
{
public:
    SpecialShapeTwo(int p1, int p2);

    virtual ~SpecialShapeTwo();

protected:
    void computeTriangles();

};

#endif // SPECIALSHAPETWO_H
