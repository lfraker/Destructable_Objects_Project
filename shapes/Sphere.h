#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

/**
 * @class Sphere
 *
 * Sphere shape.
 */

class Sphere
    : public Shape
{
public:
    Sphere(int p1, int p2, int radius);

    virtual ~Sphere();

protected:
    void computeTriangles(); // constructs sphere's triangles
};

#endif // SPHERE_H
