#include "voronoi.h"
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <QList>
#include <QSharedPointer>
#include <array>

Shape* Voronoi::split(Shape shape)
{
    return split(shape, 2);
}

Shape* Voronoi::split(Shape shape, const int depth)
{
    int pts = static_cast<int>(pow(2, depth));
    static Shape* shapes;
    shapes = static_cast<Shape*>(calloc(pts, sizeof(Shape)));
    split(shape, shapes, shape.getCenter(), pts);
    return shapes;
}

QVector3D Voronoi::intersection(Triangle tri, QVector3D la, QVector3D lb){
    QVector3D p0 = tri.m_left;
    QVector3D p1 = tri.m_right;
    QVector3D p2 = tri.m_top;
    QVector3D p01 = p1 - p0;
    QVector3D p02 = p2 - p0;
    QVector3D lab = lb - la;
    QVector3D t = ((p01 * p02) * (la - p0)) / (-lab * (p01 * p02));
    return la + (lab * t);
}

void Voronoi::split(Shape shape, Shape* shapes, QVector3D origCtr, int shapeCt)
{
    Triangle * tris = shape.getTris();

    // Split the shape into two
    QVector3D * points = new QVector3D[2];
    generatePoints(tris, points);

    // Generate plane separating the two points
    // TODO: this breaks if both points and the origin are colinear
    QVector3D midpoint = QVector3D((points[0].x() + points[1].x())/2, (points[0].y() + points[1].y())/2, (points[0].z() + points[1].z())/2);
    QVector3D cross = QVector3D::crossProduct(points[0], points[1]);
    QVector3D cross2 = QVector3D::crossProduct(points[1], points[0]);
    Triangle bisectingPlane = Triangle(midpoint, cross, cross2);

    // Add all vertices on either side to separate shapes
    QVarLengthArray<QSharedPointer<Triangle>> tL;
    QVarLengthArray<QSharedPointer<Triangle>> tR;
    QVarLengthArray<QSharedPointer<QVector3D>> intersections;

    for(int i = 0; i < sizeof(tris)/sizeof(*tris); i++){
        float lDist = tris[i].m_left.distanceToPlane(bisectingPlane.m_left, bisectingPlane.m_right, bisectingPlane.m_top);
        float rDist = tris[i].m_right.distanceToPlane(bisectingPlane.m_left, bisectingPlane.m_right, bisectingPlane.m_top);
        float tDist = tris[i].m_top.distanceToPlane(bisectingPlane.m_left, bisectingPlane.m_right, bisectingPlane.m_top);
        if(lDist < 0 && rDist < 0 && tDist < 0){
            // entire triangle is below the plane
            tL.append(QSharedPointer<Triangle>(new Triangle(tris[i].m_left, tris[i].m_right, tris[i].m_top)));
        }
        else if (lDist >= 0 && rDist >= 0 && tDist >= 0){
            if(lDist == 0) intersections.append(QSharedPointer<QVector3D>(new QVector3D(tris[i].m_left.x(), tris[i].m_left.y(), tris[i].m_left.z())));
            if(rDist == 0) intersections.append(QSharedPointer<QVector3D>(new QVector3D(tris[i].m_right.x(), tris[i].m_right.y(), tris[i].m_right.z())));
            if(tDist == 0) intersections.append(QSharedPointer<QVector3D>(new QVector3D(tris[i].m_top.x(), tris[i].m_top.y(), tris[i].m_top.z())));

            // entire triangle is above the plane
            tR.append(QSharedPointer<Triangle>(new Triangle(tris[i].m_left, tris[i].m_right, tris[i].m_top)));
        }
        else{
            // triangle touches the plane, need to split it into constituent parts on either side of our plane
            // first, find the odd one out
            if((lDist < 0 && rDist >= 0 && tDist >= 0) || (lDist >= 0 && rDist < 0 && tDist < 0)){
                QVector3D i1 = intersection(bisectingPlane, tris[i].m_left, tris[i].m_right);
                QVector3D i2 = intersection(bisectingPlane, tris[i].m_left, tris[i].m_top);
                intersections.append(QSharedPointer<QVector3D>(new QVector3D(i1.x(), i1.y(), i1.z())));
                intersections.append(QSharedPointer<QVector3D>(new QVector3D(i2.x(), i2.y(), i2.z())));
                if(lDist < 0){
                    tL.append(QSharedPointer<Triangle>(new Triangle(tris[i].m_left, i1, i2)));
                    tR.append(QSharedPointer<Triangle>(new Triangle(tris[i].m_right, i1, i2)));
                    tR.append(QSharedPointer<Triangle>(new Triangle(tris[i].m_right, tris[i].m_top, i2)));
                }
                else{
                    tR.append(QSharedPointer<Triangle>(new Triangle(tris[i].m_left, i1, i2)));
                    tL.append(QSharedPointer<Triangle>(new Triangle(tris[i].m_right, i1, i2)));
                    tL.append(QSharedPointer<Triangle>(new Triangle(tris[i].m_right, tris[i].m_top, i2)));
                }
            }
            else if ((rDist < 0 && lDist >= 0 && tDist >= 0) || (rDist >= 0 && lDist < 0 && tDist < 0)){
                QVector3D i1 = intersection(bisectingPlane, tris[i].m_right, tris[i].m_left);
                QVector3D i2 = intersection(bisectingPlane, tris[i].m_right, tris[i].m_top);
                intersections.append(QSharedPointer<QVector3D>(new QVector3D(i1.x(), i1.y(), i1.z())));
                intersections.append(QSharedPointer<QVector3D>(new QVector3D(i2.x(), i2.y(), i2.z())));
                if(rDist < 0){
                    tL.append(QSharedPointer<Triangle>(new Triangle(tris[i].m_right, i1, i2)));
                    tR.append(QSharedPointer<Triangle>(new Triangle(tris[i].m_left, i1, i2)));
                    tR.append(QSharedPointer<Triangle>(new Triangle(tris[i].m_left, tris[i].m_top, i2)));
                }
                else{
                    tR.append(QSharedPointer<Triangle>(new Triangle(tris[i].m_right, i1, i2)));
                    tL.append(QSharedPointer<Triangle>(new Triangle(tris[i].m_left, i1, i2)));
                    tL.append(QSharedPointer<Triangle>(new Triangle(tris[i].m_left, tris[i].m_top, i2)));
                }

            }
            else if ((tDist < 0 && lDist >= 0 && rDist >= 0) || (tDist >= 0 && lDist < 0 && rDist < 0)){
                QVector3D i1 = intersection(bisectingPlane, tris[i].m_top, tris[i].m_left);
                QVector3D i2 = intersection(bisectingPlane, tris[i].m_top, tris[i].m_right);
                intersections.append(QSharedPointer<QVector3D>(new QVector3D(i1.x(), i1.y(), i1.z())));
                intersections.append(QSharedPointer<QVector3D>(new QVector3D(i2.x(), i2.y(), i2.z())));
                if(tDist < 0){
                    tL.append(QSharedPointer<Triangle>(new Triangle(tris[i].m_top, i1, i2)));
                    tR.append(QSharedPointer<Triangle>(new Triangle(tris[i].m_right, i1, i2)));
                    tR.append(QSharedPointer<Triangle>(new Triangle(tris[i].m_right, tris[i].m_left, i2)));
                }else{
                    tR.append(QSharedPointer<Triangle>(new Triangle(tris[i].m_top, i1, i2)));
                    tL.append(QSharedPointer<Triangle>(new Triangle(tris[i].m_right, i1, i2)));
                    tL.append(QSharedPointer<Triangle>(new Triangle(tris[i].m_right, tris[i].m_left, i2)));
                }
            }
        }

        // Finally use the intersection points to triangulate the cleavage surface and add these triangles to both shapes
        QVarLengthArray<Triangle> triCleav;
        //intersections

        map<QVector3D, bool> matches;

        // Add all the triangles to both shapes
        Triangle * triCleavArray = triCleav.data();
        for(int i = 0; i < sizeof(triCleavArray)/sizeof(*triCleavArray); i++){
            Triangle t = triCleavArray[i];
            tL.append(QSharedPointer<Triangle>(new Triangle(t.m_left, t.m_right, t.m_top)));
            tR.append(QSharedPointer<Triangle>(new Triangle(t.m_left, t.m_right, t.m_top)));
        }
    }

    Shape shapeL = Shape(tL.data()->data());
    Shape shapeR = Shape(tR.data()->data());

    if(shapeCt == 2){
        // add direction and put the shapes in the array
        shapeL.setDirection(shapeL.getCenter() - origCtr);
        shapeR.setDirection(shapeR.getCenter() - origCtr);
        shapes[0] = shapeL;
        shapes[1] = shapeR;
        return;
    }
    else{
        // recursively keep splitting!
        split(shapeL, shapes, origCtr, shapeCt/2);
        split(shapeR, &shapes[shapeCt/2], origCtr, shapeCt/2);
    }
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
