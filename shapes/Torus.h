#ifndef TORUS_H
#define TORUS_H

#include "Shape.h"

/**
 * @class Torus
 *
 * Torus shape.
 */

class Torus
    : public Shape
{
public:
    Torus(int p1, int p2);

    virtual ~Torus();

protected:
    void computeTriangles(); // constructs Torus's triangles
};

#endif // TORUS_H
