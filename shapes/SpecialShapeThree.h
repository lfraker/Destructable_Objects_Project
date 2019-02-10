#ifndef SPECIALSHAPETHREE_H
#define SPECIALSHAPETHREE_H

#include "Shape.h"

class SpecialShapeThree
        : public Shape
{
public:
    SpecialShapeThree(int p1, int p2);

    virtual ~SpecialShapeThree();

protected:
    void computeTriangles();

};

#endif // SPECIALSHAPETHREE_H
