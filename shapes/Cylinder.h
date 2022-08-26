#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.h"

/**
 * @class Cylinder
 *
 * Cylinder shape.
 */

class Cylinder
   : public Shape
{
public:
    Cylinder(int p1, int p2, int radius);

    virtual ~Cylinder();

protected:
    void computeTriangles(); // constructs cylinder's triangles
};

#endif // CYLINDER_H
