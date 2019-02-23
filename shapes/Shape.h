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

    struct Triangle {
        QVector3D m_left;
        QVector3D m_right;
        QVector3D m_top;

        Triangle(QVector3D left, QVector3D right, QVector3D top)
        {
            m_left = left;
            m_right = right;
            m_top = top;
        }

        Triangle() { }

        int addElements(QVector3D verts[], int startInd)
        {
            verts[startInd] = m_left;
            startInd++;
            verts[startInd] = m_right;
            startInd++;
            verts[startInd] = m_top;
            startInd++;
            return startInd;
        }

//        ~Triangle()
//        {

//        }
    };

    //Constructor for Shape. Pass in parameter1 and 2 determining the number of triangles that make up the shape
    Shape(int p1, int p2);

    //Destructor for Shape.
    virtual ~Shape();

    void genVecs();
    QVector3D* getVecs(); // Return shape's vertex data
    Triangle* getTris();

    //void setParams(); // Set settings parameters and call Compute Triangle

    //void addVertNorm(glm::vec3 vert, glm::vec3 norm); // Adds a vertex and a normal to the array

    int numVertices(); // returns the number of vertices in the array.

    //int numInds(); // returns the number of indices in the array.e

    void deleteVertexCache();


protected:

    virtual void computeTriangles() = 0; // constructs shape's triangles

    int m_param1;
    int m_param2;
    //int m_numbInds;
    int m_numVerts;
    int m_numTris;
    Triangle * m_triangles = NULL;
    float m_radius;
    QVector3D* m_vertices = NULL;

};

#endif // SHAPE_H
