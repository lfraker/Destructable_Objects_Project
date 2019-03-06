#ifndef VORONOI_H
#define VORONOI_H

#include "shapes/Shape.h"

class Voronoi
{
public:
    static Shape* split(Shape);
    static Shape* split(Shape, int);
    static void split(Shape, Shape*, QVector3D, int);
    static void generatePoints(Triangle[], QVector3D[]);

private:
    static QVector3D intersection(Triangle, QVector3D, QVector3D);
    static void triangulate(Triangle[], Triangle&);
    static bool match(Triangle, QVector3D);
};

#endif // VORONOI_H
