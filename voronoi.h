#ifndef VORONOI_H
#define VORONOI_H

#include "shapes/Shape.h"

class Voronoi
{
public:
    static Shape** split(Shape*);
    static Shape** split(Shape*, int);
    static void split(Shape*, Shape**, QVector3D, int);
    static void generatePoints(Triangle[], QVector3D[], int, int);

private:
    static QVector3D intersection(Triangle, QVector3D, QVector3D);
    static void triangulate(Triangle[], Triangle&, int);
    static bool match(Triangle, QVector3D);
    static int orientation(QVector2D, QVector2D, QVector2D);
};

#endif // VORONOI_H
