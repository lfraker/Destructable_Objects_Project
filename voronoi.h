#ifndef VORONOI_H
#define VORONOI_H

#include "shapes/Shape.h"

class Voronoi
{
public:
    static Shape* split(Shape);
    static Shape* split(Shape, int);
    static void split(Shape, Shape*, int, int);
    static void generatePoints(Triangle[], QVector3D[]);

private:
    static void triangulate(Triangle[], Triangle&);
    static bool match(Triangle, QVector3D);
    static bool fequal(float, float);
};

#endif // VORONOI_H
