#include "voronoi.h"
#include <float.h>
#include <math.h>
#include <stdlib.h>

Shape* Voronoi::split(Shape shape)
{
    return split(shape, 2);
}

Shape* Voronoi::split(Shape shape, const int depth)
{
    int pts = pow(2, depth);
    static Shape* shapes;
    shapes = (Shape*) calloc(pts, sizeof(Shape));
    split(shape, shapes, 0, depth);
    return shapes;
}

void Voronoi::split(Shape shape, Shape* shapes, int shapePtr, int depth)
{
    // Split the shape into two
    QVector3D * points = new QVector3D[2];
    generatePoints(shape.getTris(), points);
    // Generate plane separating the two points
    QVector3D midpoint = QVector3D((points[0].x() + points[1].x())/2, (points[0].y() + points[1].y())/2, (points[0].z() + points[1].z())/2);
    QVector3D cross = QVector3D::crossProduct(points[0], points[1]);
    QVector3D origin = QVector3D(0, 0, 0);
    // Find where plane intersects with shape

    // Add all vertices on either side to separate shapes

    if(depth == 1){
        // put the shapes in the array and return

        return;
    }else{
        // recursively keep splitting!

    }

}

bool Voronoi::fequal(float a, float b)
{
    return (fabs(a-b) < FLT_EPSILON);
}

bool Voronoi::match(Triangle t1, QVector3D v2){
    // return if any of the three coordinates match
    return qFuzzyCompare(t1.m_left, v2) || qFuzzyCompare(t1.m_top, v2) || qFuzzyCompare(t1.m_right, v2);
}

void Voronoi::triangulate(Triangle tri[], Triangle & triangulation){
    // Generate a random triangle within the shape
    int triLength = sizeof(tri)/sizeof(*tri);
    // pick random point
    Triangle firstTriangle = tri[rand() % triLength];
    int secondIdx = rand() % triLength;
    while(match(firstTriangle, tri[secondIdx].m_left)){
        secondIdx = (secondIdx + 1) % triLength;
    }
    int thirdIdx = rand() % triLength;
    while(match(firstTriangle, tri[thirdIdx].m_left) || match(tri[secondIdx], tri[thirdIdx].m_left)){
        thirdIdx = (thirdIdx + 1) % triLength;
    }
    triangulation = Triangle(firstTriangle.m_left, tri[secondIdx].m_left, tri[thirdIdx].m_left);
}

void Voronoi::generatePoints(Triangle tri[], QVector3D pts[]){
    // Distribute points internal to the convex shape
    for(int i = 0; i < sizeof(pts) / sizeof(*pts); i++){
        // Triangulate the polygon
        Triangle triangulation;
        triangulate(tri, triangulation);
        // Pick random point on the triangle, weighted by area
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float s = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        pts[i] = ((1 - sqrt(s))*triangulation.m_top) + sqrt(s)*((1-r)*triangulation.m_left + r*triangulation.m_right);
    }
}
