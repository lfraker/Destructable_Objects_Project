/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <shapes/Cube.h>
#include <shapes/Cylinder.h>
#include <shapes/Cone.h>
#include <shapes/Sphere.h>
#include "voronoi.h"

//class GeometryEngine;

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:

    struct TransformDetails {
        public:
            QVector3D m_shapeTranslate;
    };

    enum ShapeType { SphereType, CylinderType, ConeType, CubeType};
    explicit MainWidget(QWidget *parent = 0);
    void destructObj(int depth);
    void pauseResumeSplit(bool pause);
    void advanceSplitIncr();
    void reset();
    void changeShapeType(ShapeType newType);
    void sliderChanged(bool p1, int val);
    void zoom(int zoomVal);
    void pan(int leftRight, int upDown);
    ~MainWidget();

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void deleteShapeResources();

    void initShaders();
    void initTextures();
    void refreshShape();
    void resetGl();

private:
    QBasicTimer timer;
    QOpenGLShaderProgram m_program;
    //GeometryEngine *geometries;

    QOpenGLTexture *texture;

    QMatrix4x4 projection;

//    GLuint vertexLocation;
//    GLuint colorLocation;
//    GLuint matrixLocation;
    int p1 = 10;
    int p2 = 10;

    QVector2D mousePressPosition;
    QVector3D m_camRotationAxis;
    qreal m_camAngularSpeed = 0;
    QQuaternion m_camRotation;
    QVector3D m_camZoom = QVector3D(1.0, 1.0, 1.0);
    QVector3D m_camTranslate = QVector3D(0.0, 0.0, 0.0);
    double m_camTranslateFactor = 0.2;
    double m_camZoomFactor = 0.2;
    Shape *m_shape;

    ShapeType m_shapeType = CylinderType;

    int m_numShapes = 1;
    Shape ** m_shapes = NULL;
    QOpenGLVertexArrayObject ** m_vaos = NULL;
    QOpenGLBuffer ** m_positionBuffers = NULL;
    TransformDetails * m_transforms = NULL;
    bool m_pauseSplit = true;
};

#endif // MAINWIDGET_H
