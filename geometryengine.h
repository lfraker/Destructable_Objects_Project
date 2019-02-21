#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <shapes/Cone.h>
#include <shapes/Sphere.h>

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine();
    virtual ~GeometryEngine();
    void drawCubeGeometry(QOpenGLShaderProgram *program, QMatrix4x4 projection, QQuaternion rotation);
    void drawCubeGeoTwo(QOpenGLShaderProgram *program);

private:
    void initCubeGeometry();
    Shape *m_shape;
    Shape *m_shape2;
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer arrayBuf2;
    QOpenGLBuffer indexBuf;
};

#endif // GEOMETRYENGINE_H
