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
    //QVector3D i = la + (QVector3D::crossProduct(p01, p02) * (la - p0)) / (-QVector3D::crossProduct(p01, p02));
    QVector3D n = QVector3D::crossProduct(p01, p02);
    QVector3D d = QVector3D::crossProduct((p0 - la), n) / QVector3D::crossProduct(lab, n);
    QVector3D i = d * lab + la;
    return i;
}

int Voronoi::orientation(QVector2D a, QVector2D b, QVector2D c)
{
    float val = (b.y() - a.y()) * (c.x() - b.x()) -
              (b.x() - a.x()) * (c.y() - b.y());

    if (qFuzzyCompare(val, 0.0f)) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

void Voronoi::split(Shape* shape, Shape** shapes, QVector3D origCtr, int shapeCt)
{
    qDebug("Starting split with %i tris", shape->numTris());

    // Add all vertices on either side to separate shapes
    QVarLengthArray<Triangle> tL;
    QVarLengthArray<Triangle> tR;
    QVector<QVector3D> intersections;
    Triangle * tris = shape->getTris();

    if(shape->numTris() > 0){
        // Split the shape into two
        int num_pts = 2;
        QVector3D * points = new QVector3D[num_pts];
        generatePoints(tris, points, shape->numTris(), num_pts);

        if(!qFuzzyCompare(points[0], points[1])){
            // Generate plane separating the two points
            qDebug("Generating plane to split (%f, %f, %f) and (%f, %f, %f)", points[0].x(), points[0].y(), points[0].z(), points[1].x(), points[1].y(), points[1].z());
            QVector3D a = QVector3D((points[0].x() + points[1].x())/2, (points[0].y() + points[1].y())/2, (points[0].z() + points[1].z())/2);
            QVector3D b = QVector3D::crossProduct(points[0], points[1]);
            QVector3D c = QVector3D::crossProduct(points[1], points[0]);
            Triangle bisectingPlane = Triangle(a, b, c);

            for(int i = 0; i < shape->numTris(); i++){
                float lDist = tris[i].m_left.distanceToPlane(a, b, c);
                float rDist = tris[i].m_right.distanceToPlane(a, b , c);
                float tDist = tris[i].m_top.distanceToPlane(a, b, c);
                if(lDist < 0 && rDist < 0 && tDist < 0){
                    // entire triangle is below the plane
                    tL.append(Triangle(tris[i].m_left, tris[i].m_right, tris[i].m_top));
                }
                else if (lDist >= 0 && rDist >= 0 && tDist >= 0){
                    if(qFuzzyCompare(lDist, 0)) { intersections.append(QVector3D(tris[i].m_left.x(), tris[i].m_left.y(), tris[i].m_left.z())); }
                    if(qFuzzyCompare(rDist, 0)) { intersections.append(QVector3D(tris[i].m_right.x(), tris[i].m_right.y(), tris[i].m_right.z())); }
                    if(qFuzzyCompare(tDist, 0)) { intersections.append(QVector3D(tris[i].m_top.x(), tris[i].m_top.y(), tris[i].m_top.z())); }

                    // entire triangle is above the plane
                    tR.append(Triangle(tris[i].m_left, tris[i].m_right, tris[i].m_top));
                }
                else{
                    // triangle touches the plane, need to split it into constituent parts on either side of our plane
                    // first, find the odd one out
                    if((lDist < 0 && rDist >= 0 && tDist >= 0) || (lDist >= 0 && rDist < 0 && tDist < 0)){
                        QVector3D i1 = intersection(bisectingPlane, tris[i].m_right, tris[i].m_left);
                        QVector3D i2 = intersection(bisectingPlane, tris[i].m_top, tris[i].m_left);
                        if(!intersections.contains(i1)) intersections.append(i1);
                        if(!intersections.contains(i2)) intersections.append(i2);
                        if(lDist < 0){
                            tL.append(Triangle(tris[i].m_left, i1, i2));
                            if(tris[i].m_right.distanceToPoint(i1) <= tris[i].m_top.distanceToPoint(i1) ||
                               tris[i].m_right.distanceToPoint(i2) <= tris[i].m_top.distanceToPoint(i2)){
                                tR.append(Triangle(i1, tris[i].m_right, i2));
                                if(tris[i].m_top.distanceToPoint(i1) <= tris[i].m_top.distanceToPoint(i2)){
                                    tR.append(Triangle(i1, tris[i].m_right, tris[i].m_top));
                                }else{
                                    tR.append(Triangle(i2, tris[i].m_right, tris[i].m_top));
                                }
                            }else{
                                tR.append(Triangle(i1, i2, tris[i].m_top));
                                if(tris[i].m_right.distanceToPoint(i1) <= tris[i].m_right.distanceToPoint(i2)){
                                    tR.append(Triangle(i1, tris[i].m_right, tris[i].m_top));
                                }else{
                                    tR.append(Triangle(i2, tris[i].m_right, tris[i].m_top));
                                }
                            }
                        }
                        else{
                            tR.append(Triangle(tris[i].m_left, i1, i2));
                            if(tris[i].m_right.distanceToPoint(i1) <= tris[i].m_top.distanceToPoint(i1) ||
                               tris[i].m_right.distanceToPoint(i2) <= tris[i].m_top.distanceToPoint(i2)){
                                tL.append(Triangle(i1, tris[i].m_right, i2));
                                if(tris[i].m_top.distanceToPoint(i1) <= tris[i].m_top.distanceToPoint(i2)){
                                    tL.append(Triangle(i1, tris[i].m_right, tris[i].m_top));
                                }else{
                                    tL.append(Triangle(i2, tris[i].m_right, tris[i].m_top));
                                }
                            }else{
                                tL.append(Triangle(i1, i2, tris[i].m_top));
                                if(tris[i].m_right.distanceToPoint(i1) <= tris[i].m_right.distanceToPoint(i2)){
                                    tL.append(Triangle(i1, tris[i].m_right, tris[i].m_top));
                                }else{
                                    tL.append(Triangle(i2, tris[i].m_right, tris[i].m_top));
                                }
                            }
                        }
                    }
                    else if ((rDist < 0 && lDist >= 0 && tDist >= 0) || (rDist >= 0 && lDist < 0 && tDist < 0)){
                        QVector3D i1 = intersection(bisectingPlane, tris[i].m_left, tris[i].m_right);
                        QVector3D i2 = intersection(bisectingPlane, tris[i].m_top, tris[i].m_right);
                        if(!intersections.contains(i1)) intersections.append(i1);
                        if(!intersections.contains(i2)) intersections.append(i2);
                        if(rDist < 0){
                            tL.append(Triangle(i1, tris[i].m_right, i2));
                            if(tris[i].m_left.distanceToPoint(i1) <= tris[i].m_top.distanceToPoint(i1) ||
                               tris[i].m_left.distanceToPoint(i2) <= tris[i].m_top.distanceToPoint(i2)){
                                tR.append(Triangle(tris[i].m_left, i1, i2));
                                if(tris[i].m_top.distanceToPoint(i1) <= tris[i].m_top.distanceToPoint(i2)){
                                    tR.append(Triangle(tris[i].m_left, i1, tris[i].m_top));
                                }else{
                                    tR.append(Triangle(tris[i].m_left, i2, tris[i].m_top));
                                }
                            }else{
                                tR.append(Triangle(i1, i2, tris[i].m_top));
                                if(tris[i].m_left.distanceToPoint(i1) <= tris[i].m_left.distanceToPoint(i2)){
                                    tR.append(Triangle(tris[i].m_left, i1, tris[i].m_top));
                                }else{
                                    tR.append(Triangle(tris[i].m_left, i2, tris[i].m_top));
                                }
                            }
                        }
                        else{
                            tR.append(Triangle(i1, tris[i].m_right, i2));
                            if(tris[i].m_left.distanceToPoint(i1) <= tris[i].m_top.distanceToPoint(i1) ||
                               tris[i].m_left.distanceToPoint(i2) <= tris[i].m_top.distanceToPoint(i2)){
                                tL.append(Triangle(tris[i].m_left, i1, i2));
                                if(tris[i].m_top.distanceToPoint(i1) <= tris[i].m_top.distanceToPoint(i2)){
                                    tL.append(Triangle(tris[i].m_left, i1, tris[i].m_top));
                                }else{
                                    tL.append(Triangle(tris[i].m_left, i2, tris[i].m_top));
                                }
                            }else{
                                tL.append(Triangle(i1, i2, tris[i].m_top));
                                if(tris[i].m_left.distanceToPoint(i1) <= tris[i].m_left.distanceToPoint(i2)){
                                    tL.append(Triangle(tris[i].m_left, i1, tris[i].m_top));
                                }else{
                                    tL.append(Triangle(tris[i].m_left, i2, tris[i].m_top));
                                }
                            }
                        }

                    }
                    else if ((tDist < 0 && lDist >= 0 && rDist >= 0) || (tDist >= 0 && lDist < 0 && rDist < 0)){
                        QVector3D i1 = intersection(bisectingPlane, tris[i].m_left, tris[i].m_top);
                        QVector3D i2 = intersection(bisectingPlane, tris[i].m_right, tris[i].m_top);
                        if(!intersections.contains(i1)) intersections.append(i1);
                        if(!intersections.contains(i2)) intersections.append(i2);
                        if(tDist < 0){
                            tL.append(Triangle(i1, i2, tris[i].m_top));
                            if(tris[i].m_left.distanceToPoint(i1) <= tris[i].m_right.distanceToPoint(i1) ||
                               tris[i].m_left.distanceToPoint(i2) <= tris[i].m_right.distanceToPoint(i2)){
                                tR.append(Triangle(tris[i].m_left, i1, i2));
                                if(tris[i].m_right.distanceToPoint(i1) <= tris[i].m_right.distanceToPoint(i2)){
                                    tR.append(Triangle(tris[i].m_left, tris[i].m_right, i1));
                                }else{
                                    tR.append(Triangle(tris[i].m_left, tris[i].m_right, i2));
                                }
                            }else{
                                tR.append(Triangle(i1, tris[i].m_right, i2));
                                if(tris[i].m_left.distanceToPoint(i1) <= tris[i].m_left.distanceToPoint(i2)){
                                    tR.append(Triangle(tris[i].m_left, tris[i].m_right, i1));
                                }else{
                                    tR.append(Triangle(tris[i].m_left, tris[i].m_right, i2));
                                }
                            }
                        }else{
                            tR.append(Triangle(i1, i2, tris[i].m_top));
                            if(tris[i].m_left.distanceToPoint(i1) <= tris[i].m_right.distanceToPoint(i1) ||
                               tris[i].m_left.distanceToPoint(i2) <= tris[i].m_right.distanceToPoint(i2)){
                                tL.append(Triangle(tris[i].m_left, i1, i2));
                                if(tris[i].m_right.distanceToPoint(i1) <= tris[i].m_right.distanceToPoint(i2)){
                                    tL.append(Triangle(tris[i].m_left, tris[i].m_right, i1));
                                }else{
                                    tL.append(Triangle(tris[i].m_left, tris[i].m_right, i2));
                                }
                            }else{
                                tL.append(Triangle(tris[i].m_right, i1, i2));
                                if(tris[i].m_left.distanceToPoint(i1) <= tris[i].m_left.distanceToPoint(i2)){
                                    tL.append(Triangle(tris[i].m_left, tris[i].m_right, i1));
                                }else{
                                    tL.append(Triangle(tris[i].m_left, tris[i].m_right, i2));
                                }
                            }
                        }
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
            float x = 0;
            float y = 0;
            int leftMost = -1;
            QVarLengthArray<QVector2D> intersections2d;
            for(int i = 0; i < intersections.size(); i++){
                qDebug("intersections %i: %f, %f, %f", i, intersections[i].x(), intersections[i].y(), intersections[i].z());
                QVector4D p = QVector4D(intersections[i].x(), intersections[i].y(), intersections[i].z(), 1);
                QVector4D p2 = m * p;
                intersections2d.append(QVector2D(p2.x(), p2.y()));
                if(p2.x() < minX) { minX = p2.x(); leftMost = i; }
                if(p2.y() < minY) minY = p2.y();
                if(p2.x() > maxX) maxX = p2.x();
                if(p2.y() > maxY) maxY = p2.y();
                x += p2.x();
                y += p2.y();
            }

            // Build triangulation in 2D
            qDebug("max x %f, min x %f, max y %f, min y %f", maxX, minX, maxY, minY);
            QVector2D center1 = QVector2D(x/intersections.size(), y/intersections.size() + ((maxY - minY)/3.0f));
            QVector2D center2 = QVector2D(x/intersections.size() - ((maxX - minX)/4.5f), y/intersections.size() - ((maxY - minY)/6.0f));
            QVector2D center3 = QVector2D(x/intersections.size() + ((maxX - minX)/4.5f), y/intersections.size() - ((maxY - minY)/6.0f));
            qDebug("c1: %f, %f", center1.x(), center1.y());
            qDebug("c2: %f, %f", center2.x(), center2.y());
            qDebug("c3: %f, %f", center3.x(), center3.y());
            // Build triangles around center point
            // Translate the 2D triangulation back to 3D
            if(intersections2d.size() > 0){
                QVarLengthArray<Triangle> triCleav;
                QVarLengthArray<QVector2D> poly;
                int p = leftMost;
                int q;
                do
                {
                    poly.append(QVector2D(intersections2d[p].x(), intersections2d[p].y()));
                    // search through points counter clockwise
                    q = (p + 1) % intersections2d.size();
                    for (int i = 0; i < intersections2d.size(); i++)
                    {
                       if (orientation(intersections2d[p], intersections2d[i], intersections2d[q]) == 2){
                           q = i;
                       }
                    }

                    p = q;
                } while (p != leftMost);
                poly.append(QVector2D(intersections2d[p].x(), intersections2d[p].y()));

                for(int i = 0; i < poly.size() - 1; i++){
                    QVector4D p1 = QVector4D(poly[i].x(), poly[i].y(), 0, 1);
                    QVector4D p2 = QVector4D(poly[i + 1].x(), poly[i + 1].y(), 0, 1);
                    QVector4D p3;
                    float c1 = abs(poly[i].distanceToPoint(center1));
                    float c2 = abs(poly[i].distanceToPoint(center2));
                    float c3 = abs(poly[i].distanceToPoint(center3));
                    if(c1 <= c2 && c1 <= c3) { qDebug("c1"); p3 = QVector4D(center1.x(), center1.y(), 0, 1); }
                    if(c2 <= c1 && c2 <= c3) { qDebug("c2"); p3 = QVector4D(center2.x(), center2.y(), 0, 1); }
                    if(c3 <= c1 && c3 <= c2) { qDebug("c3"); p3 = QVector4D(center3.x(), center3.y(), 0, 1); }
                    //QVector4D p3 = QVector4D(center.x(), center.y(), 0, 1);
                    QVector3D l, r, t;
                    // Orient and create our new triangle
                    if(p1.x() < p2.x() && p1.x() < p3.x()){
                        p1 = mInv * p1;
                        l = QVector3D(p1.x(), p1.y(), p1.z());
                        if(p2.x() > p3.x()){
                            p2 = mInv * p2;
                            r = QVector3D(p2.x(), p2.y(), p2.z());
                            p3 = mInv * p3;
                            t = QVector3D(p3.x(), p3.y(), p3.z());
                        }else{
                            p2 = mInv * p2;
                            t = QVector3D(p2.x(), p2.y(), p2.z());
                            p3 = mInv * p3;
                            r = QVector3D(p3.x(), p3.y(), p3.z());
                        }
                    }else if(p2.x() < p1.x() && p2.x() < p3.x()){
                        p2 = mInv * p2;
                        l = QVector3D(p2.x(), p2.y(), p2.z());
                        if(p1.x() > p3.x()){
                            p1 = mInv * p1;
                            r = QVector3D(p1.x(), p1.y(), p1.z());
                            p3 = mInv * p3;
                            t = QVector3D(p3.x(), p3.y(), p3.z());
                        }else{
                            p1 = mInv * p1;
                            t = QVector3D(p1.x(), p1.y(), p1.z());
                            p3 = mInv * p3;
                            r = QVector3D(p3.x(), p3.y(), p3.z());
                        }
                    }else{
                        p3 = mInv * p3;
                        l = QVector3D(p3.x(), p3.y(), p3.z());
                        if(p1.x() > p2.x()){
                            p1 = mInv * p1;
                            r = QVector3D(p1.x(), p1.y(), p1.z());
                            p2 = mInv * p2;
                            t = QVector3D(p2.x(), p2.y(), p2.z());
                        }else{
                            p1 = mInv * p1;
                            t = QVector3D(p1.x(), p1.y(), p1.z());
                            p2 = mInv * p2;
                            r = QVector3D(p2.x(), p2.y(), p2.z());
                        }
                    }
                    triCleav.append(Triangle(l, r, t));
                }

                QVector4D c1 = mInv * QVector4D(center1.x(), center1.y(), 0, 1);
                QVector4D c2 = mInv * QVector4D(center2.x(), center2.y(), 0, 1);
                QVector4D c3 = mInv * QVector4D(center3.x(), center3.y(), 0, 1);
                triCleav.append(Triangle(c2.toVector3D(), c3.toVector3D(), c1.toVector3D()));

                // Add all the triangles to both shapes
                for(int i = 0; i < triCleav.size(); i++){
                    tL.append(triCleav[i]);
                    tR.append(triCleav[i]);
                }
            }
        }else{
            // Can't triangulate, but don't want to lose the triangles
            for (int i = 0; i < shape->numTris(); i++) {
                tL.append(tris[i]);
            }
        }
    }

    qDebug("Creating shapes from triangle data");
    Shape* shapeL = new Shape(tL.data(), tL.size());
    Shape* shapeR = new Shape(tR.data(), tR.size());

    if(shapeCt == 2){
        // add direction and put the shapes in the array
        QVector3D centL = shapeL->getCenter();
        QVector3D centR = shapeR->getCenter();
        shapeL->setDirectionCenter(centL - origCtr, centL);
        shapeR->setDirectionCenter(centR - origCtr, centR);
        shapes[0] = shapeL;
        shapes[1] = shapeR;
        return;
    }
    else{
        // recursively keep splitting!
        qDebug("split1 %i", shapeCt/2);
        split(shapeL, shapes, origCtr, shapeCt/2);
        qDebug("split2 %i", shapeCt/2);
        split(shapeR, shapes + (shapeCt/2), origCtr, shapeCt/2);
    }
}

bool Voronoi::match(Triangle t1, QVector3D v2){
    // return if any of the three coordinates match
    return qFuzzyCompare(t1.m_left, v2) || qFuzzyCompare(t1.m_top, v2) || qFuzzyCompare(t1.m_right, v2);
}

void Voronoi::triangulate(Triangle tri[], Triangle & triangulation, int num_tris){
    // Generate a random triangle within the shape
    // pick random point
    Triangle firstTriangle = tri[rand() % num_tris];
    int secondIdx = rand() % num_tris;
    int attempts = 0;
    while(match(firstTriangle, tri[secondIdx].m_left)){
        attempts++;
        if(attempts > num_tris) return;
        secondIdx = (secondIdx + 1) % num_tris;
    }
    int thirdIdx = rand() % num_tris;
    attempts = 0;
    while(match(firstTriangle, tri[thirdIdx].m_left) || match(tri[secondIdx], tri[thirdIdx].m_left)){
        attempts++;
        if(attempts > num_tris) return;
        thirdIdx = (thirdIdx + 1) % num_tris;
    }
    triangulation = Triangle(firstTriangle.m_left, tri[secondIdx].m_left, tri[thirdIdx].m_left);
}

void Voronoi::generatePoints(Triangle tri[], QVector3D pts[], int num_tris, int num_pts){
    // Distribute points internal to the convex shape
    for(int i = 0; i < num_pts; i++){
        qDebug("triangulating point %i", i);
        // Triangulate the polygon
        Triangle triangulation;
        triangulate(tri, triangulation, num_tris);
        // Pick random point on the triangle, weighted by area
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float s = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        pts[i] = ((1 - sqrt(s))*triangulation.m_top) + sqrt(s)*((1-r)*triangulation.m_left + r*triangulation.m_right);
    }
}
