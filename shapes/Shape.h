#ifndef SHAPE_H
#define SHAPE_H

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

    //Destructor for Shape.
    virtual ~Shape();

    QVector3D* getVecs(); // Return shape's vertex data

    //void setParams(); // Set settings parameters and call Compute Triangle

    //void addVertNorm(glm::vec3 vert, glm::vec3 norm); // Adds a vertex and a normal to the array

    int numVertices(); // returns the number of vertices in the array.

    //int numInds(); // returns the number of indices in the array.e


protected:

    virtual void computeTriangles() = 0; // constructs shape's triangles

    int m_param1;
    int m_param2;
    //int m_numbInds;
    int m_numVerts;
    QVector3D* m_vertexData;
    float m_radius;


};

#endif // SHAPE_H
