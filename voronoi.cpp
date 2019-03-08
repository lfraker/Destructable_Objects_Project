#include "voronoi.h"
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <QList>
#include <QMatrix4x4>
#include <QSharedPointer>
#include <array>

Shape** Voronoi::split(Shape* shape)
{
    return split(shape, 2);
}

Shape** Voronoi::split(Shape* shape, const int depth)
{
    int pts = static_cast<int>(pow(2, depth));
    Shape ** shapes;
    shapes = new Shape * [pts];
    split(shape, shapes, shape->getCenter(), pts);
    return shapes;
}

QVector3D Voronoi::intersection(Triangle tri, QVector3D la, QVector3D lb){
    QVector3D p0 = tri.m_left;
    QVector3D p1 = tri.m_right;
    QVector3D p2 = tri.m_top;
    QVector3D p01 = p1 - p0;
    QVector3D p02 = p2 - p0;
    QVector3D lab = lb - la;
    QVector3D t = (QVector3D::crossProduct(p01, p02) * (la - p0)) / (-lab * QVector3D::crossProduct(p01, p02));
    return la + (lab * t);
}

void Voronoi::split(Shape* shape, Shape** shapes, QVector3D origCtr, int shapeCt)
{
    Triangle * tris = shape->getTris();

    // Split the shape into two
    int num_pts = 2;
    QVector3D * points = new QVector3D[num_pts];
    generatePoints(tris, points, shape->numTris(), num_pts);

    // Generate plane separating the two points
    // TODO: this all breaks if both points and the origin are colinear
    QVector3D a = QVector3D((points[0].x() + points[1].x())/2, (points[0].y() + points[1].y())/2, (points[0].z() + points[1].z())/2);
    QVector3D b = QVector3D::crossProduct(points[0], points[1]);
    QVector3D c = QVector3D::crossProduct(points[1], points[0]);
    Triangle bisectingPlane = Triangle(a, b, c);

    // Add all vertices on either side to separate shapes
    QVarLengthArray<Triangle> tL;
    QVarLengthArray<Triangle> tR;
    QVarLengthArray<QVector3D> intersections;

    for(unsigned int i = 0; i < shape->numTris(); i++){
        float lDist = tris[i].m_left.distanceToPlane(bisectingPlane.m_left, bisectingPlane.m_right, bisectingPlane.m_top);
        float rDist = tris[i].m_right.distanceToPlane(bisectingPlane.m_left, bisectingPlane.m_right, bisectingPlane.m_top);
        float tDist = tris[i].m_top.distanceToPlane(bisectingPlane.m_left, bisectingPlane.m_right, bisectingPlane.m_top);
        if(lDist < 0 && rDist < 0 && tDist < 0){
            // entire triangle is below the plane
            tL.append(Triangle(tris[i].m_left, tris[i].m_right, tris[i].m_top));
        }
        else if (lDist >= 0 && rDist >= 0 && tDist >= 0){
            if(lDist == 0.0f) intersections.append(QVector3D(tris[i].m_left.x(), tris[i].m_left.y(), tris[i].m_left.z()));
            if(rDist == 0.0f) intersections.append(QVector3D(tris[i].m_right.x(), tris[i].m_right.y(), tris[i].m_right.z()));
            if(tDist == 0.0f) intersections.append(QVector3D(tris[i].m_top.x(), tris[i].m_top.y(), tris[i].m_top.z()));

            // entire triangle is above the plane
            tR.append(Triangle(tris[i].m_left, tris[i].m_right, tris[i].m_top));
        }
        else{
            // triangle touches the plane, need to split it into constituent parts on either side of our plane
            // first, find the odd one out
            if((lDist < 0 && rDist >= 0 && tDist >= 0) || (lDist >= 0 && rDist < 0 && tDist < 0)){
                QVector3D i1 = intersection(bisectingPlane, tris[i].m_left, tris[i].m_right);
                QVector3D i2 = intersection(bisectingPlane, tris[i].m_left, tris[i].m_top);
                intersections.append(QVector3D(i1.x(), i1.y(), i1.z()));
                intersections.append(QVector3D(i2.x(), i2.y(), i2.z()));
                if(lDist < 0){
                    tL.append(Triangle(tris[i].m_left, i1, i2));
                    tR.append(Triangle(tris[i].m_right, i1, i2));
                    tR.append(Triangle(tris[i].m_right, tris[i].m_top, i2));
                }
                else{
                    tR.append(Triangle(tris[i].m_left, i1, i2));
                    tL.append(Triangle(tris[i].m_right, i1, i2));
                    tL.append(Triangle(tris[i].m_right, tris[i].m_top, i2));
                }
            }
            else if ((rDist < 0 && lDist >= 0 && tDist >= 0) || (rDist >= 0 && lDist < 0 && tDist < 0)){
                QVector3D i1 = intersection(bisectingPlane, tris[i].m_right, tris[i].m_left);
                QVector3D i2 = intersection(bisectingPlane, tris[i].m_right, tris[i].m_top);
                intersections.append(QVector3D(i1.x(), i1.y(), i1.z()));
                intersections.append(QVector3D(i2.x(), i2.y(), i2.z()));
                if(rDist < 0){
                    tL.append(Triangle(tris[i].m_right, i1, i2));
                    tR.append(Triangle(tris[i].m_left, i1, i2));
                    tR.append(Triangle(tris[i].m_left, tris[i].m_top, i2));
                }
                else{
                    tR.append(Triangle(tris[i].m_right, i1, i2));
                    tL.append(Triangle(tris[i].m_left, i1, i2));
                    tL.append(Triangle(tris[i].m_left, tris[i].m_top, i2));
                }

            }
            else if ((tDist < 0 && lDist >= 0 && rDist >= 0) || (tDist >= 0 && lDist < 0 && rDist < 0)){
                QVector3D i1 = intersection(bisectingPlane, tris[i].m_top, tris[i].m_left);
                QVector3D i2 = intersection(bisectingPlane, tris[i].m_top, tris[i].m_right);
                intersections.append(QVector3D(i1.x(), i1.y(), i1.z()));
                intersections.append(QVector3D(i2.x(), i2.y(), i2.z()));
                if(tDist < 0){
                    tL.append(Triangle(tris[i].m_top, i1, i2));
                    tR.append(Triangle(tris[i].m_right, i1, i2));
                    tR.append(Triangle(tris[i].m_right, tris[i].m_left, i2));
                }else{
                    tR.append(Triangle(tris[i].m_top, i1, i2));
                    tL.append(Triangle(tris[i].m_right, i1, i2));
                    tL.append(Triangle(tris[i].m_right, tris[i].m_left, i2));
                }
            }
        }

        // Finally use the intersection points to triangulate the cleavage surface and add these triangles to both shapes
        // Build 3D to 2D translation matrices
        QVector3D ab = b - a;
        QVector3D ac = c - a;
        QVector3D n = QVector3D::crossProduct(ab, ac);
        n.normalize();
        ab.normalize();
        QVector3D v = QVector3D::crossProduct(ab, n);
        QMatrix4x4 d = QMatrix4x4(0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1 ,1);
        QMatrix4x4 s = QMatrix4x4(a.x(), a.x() + ab.x(), a.x() + n.x(), a.x() + n.x(),
                                  a.y(), a.y() + ab.y(), a.y() + n.y(), a.y() + n.y(),
                                  a.z(), a.z() + ab.z(), a.z() + n.z(), a.z() + n.z(),
                                  1, 1, 1, 1);
        QMatrix4x4 sInv = s.inverted();
        QMatrix4x4 m = d * sInv;
        m = m.transposed();
        QMatrix4x4 mInv = m.inverted();


        // Convert 3D points on plane to 2D for triangulation
        float minX = std::numeric_limits<float>::max();
        float minY = std::numeric_limits<float>::max();
        float maxX = -std::numeric_limits<float>::max();
        float maxY = -std::numeric_limits<float>::max();

        QVarLengthArray<QVector3D> intersections2d;
        for(unsigned int i = 0; i < intersections.size(); i++){
            QVector4D p = QVector4D(intersections[i].x(), intersections[i].y(), intersections[i].z(), 1);
            QVector4D p2 = m * p;
            intersections2d.append(QVector2D(p2.x(), p2.y()));
            if(p2.x() < minX) minX = p2.x();
            if(p2.y() < minY) minY = p2.y();
            if(p2.x() > maxX) maxX = p2.x();
            if(p2.y() > maxY) maxY = p2.y();
        }

        // Build triangulation in 2D
        QVector2D center = QVector2D((maxX - minX)/2, (maxY - minY)/2);

        // Translate the 2D triangulation back to 3D
        QVarLengthArray<Triangle> triCleav;
        for(unsigned int i = 0; i < intersections2d.size(); i++){
            //intersections2d
            //triCleav.append(new Triangle(
        }

        // Add all the triangles to both shapes
        Triangle * triCleavArray = triCleav.data();
        for(unsigned int i = 0; i < triCleav.size(); i++){
            Triangle t = triCleavArray[i];
            tL.append(Triangle(t.m_left, t.m_right, t.m_top));
            tR.append(Triangle(t.m_left, t.m_right, t.m_top));
        }
    }

    Shape* shapeL = new Shape(tL.data(), tL.size());
    Shape* shapeR = new Shape(tR.data(), tR.size());

    if(shapeCt == 2){
        // add direction and put the shapes in the array
        shapeL->setDirection(shapeL->getCenter() - origCtr);
        shapeR->setDirection(shapeR->getCenter() - origCtr);
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

void Voronoi::triangulate(Triangle tri[], Triangle & triangulation, int num_tris){
    // Generate a random triangle within the shape
    int triLength = num_tris; //sizeof(tri)/sizeof(*tri);
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

void Voronoi::generatePoints(Triangle tri[], QVector3D pts[], int num_tris, int num_pts){
    // Distribute points internal to the convex shape
    for(unsigned int i = 0; i < num_pts; i++){
        // Triangulate the polygon
        Triangle triangulation;
        triangulate(tri, triangulation, num_tris);
        // Pick random point on the triangle, weighted by area
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float s = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        pts[i] = ((1 - sqrt(s))*triangulation.m_top) + sqrt(s)*((1-r)*triangulation.m_left + r*triangulation.m_right);
    }
}
