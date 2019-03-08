#ifndef SHAPE_H
#define SHAPE_H

#include "Triangle.h"
#include <QVector3D>
#include <QtMath>

/**
 * @class Shape
 * Superclass for all shapes.
 */

class Shape
{
public:
    //Constructor for Shape. Pass in parameter1 and 2 determining the number of triangles that make up the shape
    Shape(int p1, int p2);
    Shape(Triangle*, int length);

    //Destructor for Shape.
    virtual ~Shape();

    void genVecs();
    QVector3D* getVecs(); // Return shape's vertex data
    QVector3D getCenter();
    Triangle* getTris();

    //void setParams(); // Set settings parameters and call Compute Triangle
    void setDirection(QVector3D);
    void setTriangles(Triangle*);
    //void addVertNorm(glm::vec3 vert, glm::vec3 norm); // Adds a vertex and a normal to the array

    int numVertices(); // returns the number of vertices in the array.
    int numTris();

    //int numInds(); // returns the number of indices in the array.e

    void deleteVertexCache();

    QVector3D m_direction = QVector3D(0.0, 0.0, 0.0);


protected:

    void computeTriangles(); // constructs shape's triangles

    int m_param1;
    int m_param2;
    //int m_numbInds;
    int m_numVerts;
    int m_numTris;
    float m_radius;
    Triangle* m_triangles = NULL;
    QVector3D* m_vertices = NULL;
};

#endif // SHAPE_H
