#include "voronoi.h"
#include <float.h>
#include <math.h>
#include <stdlib.h>

Triangle * Voronoi::split(Triangle tri[])
{
    return split(tri, 2);
}

Triangle * Voronoi::split(Triangle tri[], const int pts)
{
    return split(tri, generatePoints(tri, pts));
}

Triangle * Voronoi::split(Triangle tri[], QVector3D pts[])
{
    return tri;
}

bool Voronoi::fequal(float a, float b)
{
    return (fabs(a-b) < FLT_EPSILON);
}

bool Voronoi::match(QVector3D v1, QVector3D v2){
    // return if two of the three coordinates match
    return ((fequal(v1.x(), v2.x()) && fequal(v1.y(), v2.y())) ||
            (fequal(v1.x(), v2.x()) && fequal(v1.z(), v2.z())) ||
            (fequal(v1.y(), v2.y()) && fequal(v1.z(), v2.z())));
}

void Voronoi::triangulate(Triangle tri[], Triangle & triangulation){
    // Generate a random triangle within the shape
    int triLength = sizeof(tri)/sizeof(*tri);
    int randPts[3];
    // pick random point
    QVector3D tLeft = tri[rand() % triLength].m_left;
    QVector3D tRight = tri[rand() % triLength].m_left;
    while(match(tLeft, tRight)){
        tRight = tri[rand() % triLength].m_left;
    }
    QVector3D tTop = tri[rand() % triLength].m_left;
    while(match(tLeft, tTop) || match(tRight, tTop)){
        tTop = tri[rand() % triLength].m_left;
    }
    triangulation = Triangle(tLeft, tRight, tTop);
}

QVector3D * Voronoi::generatePoints(Triangle tri[], const int pts){
    // Distribute points internal to the convex shape
    static QVector3D* rPts;
    rPts = (QVector3D*) calloc(pts, sizeof(QVector3D));
    for(int i = 0; i < pts; i++){
        // Triangulate the polygon
        Triangle triangulation;
        triangulate(tri, triangulation);
        // Pick random point on the triangle, weighted by area
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float s = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        rPts[i] = ((1 - sqrt(s))*triangulation.m_top) + sqrt(s)*((1-r)*triangulation.m_left + r*triangulation.m_right);
    }
    return rPts;
}
