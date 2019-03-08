#include "shapes/Shape.h"
#include "shapes/Triangle.h"
#include <limits>

Shape::Shape(int p1, int p2)
{
    m_param1 = p1;
    m_param2 = p2;
    m_destructShape = false;
}

Shape::Shape(Triangle* t, int length)
{
    m_numTris = length;
    this->setTriangles(t);
    m_destructShape = true;
}

int Shape::numVertices() {
    return m_numTris * 3;
}

int Shape::numTris() {
    return m_numTris;
}
void Shape::genVecs() {
    m_vertices = new QVector3D[this->numVertices()];
    int vertCtr = 0;

    for (int i = 0; i < m_numTris; i++) {
        Triangle tri = m_triangles[i];
        vertCtr = tri.addElements(m_vertices, vertCtr);
    }
}

QVector3D* Shape::getVecs() {
    return m_vertices;
}

QVector3D Shape::getCenter(){
    float x = 0;
    float y = 0;
    float z = 0;
    for(int i = 0; i < this->numVertices(); i++){
        x += m_vertices[i].x();
        y += m_vertices[i].y();
        z += m_vertices[i].z();
    }
    return QVector3D((x)/this->numVertices(), (y)/this->numVertices(), (z)/this->numVertices());
}

Triangle* Shape::getTris() {
    return m_triangles;
}

void Shape::setDirection(QVector3D v) {
    m_direction = v;
}

void Shape::setTriangles(Triangle* t)
{
    //m_numTris = sizeof(t) / sizeof (*t);
    m_triangles = t;
    genVecs();
}

Shape::~Shape() {
    if (m_triangles != NULL && !m_destructShape) {
        delete [] m_triangles;
        m_triangles = NULL;
    }

    if (m_vertices != NULL) {
        delete [] m_vertices;
        m_vertices = NULL;
    }
}
