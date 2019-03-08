#include "shapes/Shape.h"
#include "shapes/Triangle.h"
#include <limits>

Shape::Shape(int p1, int p2)
{
    m_param1 = p1;
    m_param2 = p2;
}

Shape::Shape(Triangle* t, int length)
{
    m_numTris = length;
    this->setTriangles(t);
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
    float minX = std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();
    float minZ = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::min();
    float maxY = std::numeric_limits<float>::min();
    float maxZ = std::numeric_limits<float>::min();
    for(int i = 0; i < sizeof(m_vertices) / sizeof(*m_vertices); i++){
        if(m_vertices[i].x() < minX) minX = m_vertices[i].x();
        if(m_vertices[i].y() < minY) minY = m_vertices[i].y();
        if(m_vertices[i].z() < minZ) minZ = m_vertices[i].z();
        if(m_vertices[i].x() > maxX) maxX = m_vertices[i].x();
        if(m_vertices[i].y() > maxY) maxY = m_vertices[i].y();
        if(m_vertices[i].z() > maxZ) maxZ = m_vertices[i].z();
    }
    return QVector3D((maxX - minX)/2, (maxY - minY)/2, (maxZ - minZ)/2);
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
    if (m_triangles != NULL) {
        delete [] m_triangles;
        m_triangles = NULL;
    }

    if (m_vertices != NULL) {
        delete [] m_vertices;
        m_vertices = NULL;
    }
}
