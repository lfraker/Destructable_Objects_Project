#include "shapes/Shape.h"

Shape::Shape(int p1, int p2)
{
    m_param1 = p1;
    m_param2 = p2;
}


int Shape::numVertices() {
    return m_numVerts;
}

QVector3D* Shape::getVecs() {
    return m_vertexData;
}


Shape::~Shape() {
    if (m_vertexData) {
        delete [] m_vertexData;
    }
    m_vertexData = NULL;
}
