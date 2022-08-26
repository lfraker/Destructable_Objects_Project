#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"

/**
 * @class Cube
 *
 * Cube shape.
 */

class Cube
    : public Shape
{
public:
    Cube(int p1, int p2);

    virtual ~Cube();

protected:
    void computeTriangles(); // constructs cube's triangles
};

#endif // CUBE_H
