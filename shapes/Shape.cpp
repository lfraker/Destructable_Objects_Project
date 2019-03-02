#include "shapes/Shape.h"
#include "shapes/Triangle.h"

Shape::Shape(int p1, int p2, int pts)
{
    m_param1 = p1;
    m_param2 = p2;
    m_internalPts = pts;
}

int Shape::numVertices() {
    return m_numTris * 3;
}

void Shape::genVecs() {
    m_vertices = new QVector3D[numVertices()];
    int vertCtr = 0;

    for (int i = 0; i < m_numTris; i++) {
        Triangle tri = m_triangles[i];
        vertCtr = tri.addElements(m_vertices, vertCtr);
    }
}

QVector3D* Shape::getVecs() {
    return m_vertices;
}

Triangle* Shape::getTris() {
    return m_triangles;
}

Shape::~Shape() {
    if (m_triangles != NULL) {
        delete [] m_triangles;
    }

    m_triangles = NULL;

    if (m_vertices != NULL) {
        delete [] m_vertices;
    }

    m_vertices = NULL;
}
