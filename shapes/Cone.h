#ifndef CONE_H
#define CONE_H

#include "Shape.h"

/**
 * @class Cone
 *
 * Cone shape.
 */

class Cone
    : public Shape
{
public:
    Cone(int p1, int p2, int radius);

    virtual ~Cone();

protected:
    void computeTriangles(); // constructs cone's triangles
};

#endif // CONE_H
