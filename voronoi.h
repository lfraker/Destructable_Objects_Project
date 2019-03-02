#ifndef VORONOI_H
#define VORONOI_H

#include "shapes/Triangle.h"


]

class Voronoi
{
public:
    static Triangle * split(Triangle[]);
    static Triangle * split(Triangle[], int);
    static Triangle * split(Triangle[], QVector3D[]);
    static QVector3D * generatePoints(Triangle[], int);

private:
    static void triangulate(Triangle[], Triangle&);
    static bool match(QVector3D, QVector3D);
    static bool fequal(float, float);
};

#endif // VORONOI_H
