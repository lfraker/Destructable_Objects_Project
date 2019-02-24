#ifndef VORONOI_H
#define VORONOI_H

#include "shapes/Triangle.h"

class Voronoi
{
public:
    Voronoi();

    Triangle * split(Triangle[]);
    Triangle * split(Triangle[], int);
    Triangle * split(Triangle[], QVector3D[]);
    QVector3D * generatePoints(Triangle[], int);

private:
    void triangulate(Triangle[], Triangle&);
    bool match(QVector3D, QVector3D);
    bool fequal(float, float);
};

#endif // VORONOI_H
