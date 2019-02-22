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


#include "mainwidget.h"

#include <QMouseEvent>

#include <math.h>

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    //geometries(0),
    texture(0),
    angularSpeed(0),
    m_vao1(new QOpenGLVertexArrayObject),
    m_vao2(new QOpenGLVertexArrayObject)
{
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    //delete geometries;
    delete m_shape;
    delete m_shape2;
    doneCurrent();
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::destructObj() {
    int i = 5;
}

void MainWidget::changeShapeType(ShapeType newType) {
    m_shapeType = newType;
    refreshShape();
}

void MainWidget::refreshShape() {
    delete m_shape;
    switch (m_shapeType) {
        case SphereType:
            m_shape = new Sphere(p1, p2, 1);
            break;
        case CylinderType:
            m_shape = new Cylinder(p1, p2, 1);
            break;
        case ConeType:
            m_shape = new Cone(p1, p2, 1);
            break;
        case CubeType:
            m_shape = new Cube(p1, p2);
            break;
    }
    resetGl();
    update();
}

void MainWidget::resetGl() {
    m_vao1->bind();
    m_positionBuffer1.release();
    m_positionBuffer1.bind();
    m_positionBuffer1.allocate( m_shape->getVecs(), m_shape->numVertices() * sizeof(QVector3D) );
}

void MainWidget::sliderChanged(bool param1, int val) {
    //delete m_shape;
    if (param1){
        p1 = val;
    }
    else {
        p2 = val;
    }
//    m_vao1->release();
//    m_vao1->destroy();
//    m_vao1->create();
    if (val < 5) {
        int i = 7;
    }
//    m_vao1->bind();
    refreshShape();
//    m_positionBuffer1.release();
////    m_positionBuffer1.destroy();
////    m_positionBuffer1.create();
////    m_positionBuffer1.setUsagePattern( QOpenGLBuffer::StreamDraw );
//    m_positionBuffer1.bind();
//    m_positionBuffer1.allocate( m_shape->getVecs(), m_shape->numVertices() * sizeof(QVector3D) );
////    m_program.enableAttributeArray("a_position");
////    m_program.setAttributeBuffer( "a_position", GL_FLOAT, 0, 3, sizeof(QVector3D));
//    update();
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}

void MainWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
    }
}

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    //geometries = new GeometryEngine();
//    m_vao.create();
//    m_vvbo.create();
//    m_vcbo.create();

    // Create VAO for first object to render
    m_vao1->create();
    m_vao1->bind();

    // Setup VBOs and IBO (use QOpenGLBuffer to buffer data,
    // specify format, usage hint etc). These will be
    // remembered by the currently bound VAO
    m_positionBuffer1.create();
    m_positionBuffer1.setUsagePattern( QOpenGLBuffer::StreamDraw );
    m_positionBuffer1.bind();
    m_shape = new Cylinder(10, 10, 1);
    m_shape2 = new Cube(10, 10);
    m_positionBuffer1.allocate( m_shape->getVecs(), m_shape->numVertices() * sizeof(QVector3D) );
    m_program.enableAttributeArray("a_position");
    m_program.setAttributeBuffer( "a_position", GL_FLOAT, 0, 3, sizeof(QVector3D));
    //int vertexLocation = program->attributeLocation("a_position");
    //program->enableAttributeArray(vertexLocation);
    //program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(QVector3D));

    // Repeat for buffers of normals, texture coordinates,
    // tangents, ...


//    // Create VAO for second object to render
//    m_vao2->create();
//    m_vao2->bind();
//    m_positionBuffer2.create();
//    m_positionBuffer2.setUsagePattern( QOpenGLBuffer::StreamDraw );
//    m_positionBuffer2.bind();
//    m_positionBuffer2.allocate( m_shape2->getVecs(), m_shape2->numVertices() * sizeof(QVector3D) );
//    m_program.enableAttributeArray("a_position");
//    m_program.setAttributeBuffer( "a_position", GL_FLOAT, 0, 3, sizeof(QVector3D));

    // Setup VBOs and IBO for next object

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!m_program.link())
        close();

    // Bind shader pipeline for use
    if (!m_program.bind())
        close();
}

void MainWidget::initTextures()
{
    // Load cube.png image
    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1.0, zFar = 20.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();

    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -10.0);
    matrix.rotate(rotation);

    // Set modelview-projection matrix
    m_program.setUniformValue("mvp_matrix", projection * matrix);

    // Use texture unit 0 which contains cube.png
    m_program.setUniformValue("texture", 0);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //location of vertex data arrays must be before they are referenced
    //but location not important otherwise
//    static const float vertexPositions[] = {
//    -1.0f, 0.0f, 0.0f, //(x,y,z) bottom left
//    1.0f, 0.0f, 0.0f, //bottom right
//    0.0f, 1.0f, 0.0f //top middle
//    };

//    static const float vertexColors[] = {
//    1.0f, .0f, .0f, //red (r,g,b) values for each vertex
//    .0f, 1.0f, .0f, //green
//    .0f, .0f, 1.0f //blue
//    };

//    m_vao.bind(); //sets the Vertex Array Object current to the OpenGL context so we can write attributes to it

//    QOpenGLBuffer m_vvbo(QOpenGLBuffer::VertexBuffer);
//    m_vvbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
//    m_vvbo.bind();
//    m_vvbo.allocate(vertexPositions, 9 * sizeof(float));
//    m_program.enableAttributeArray("position"); //this labels an attribute &quot;position&quot;
//    //that points to the memory slot from the last buffer allocate()
//    //the position attribute is an input to our vertex shader
//    m_program.setAttributeBuffer("position", GL_FLOAT, 0, 3);

//    QOpenGLBuffer m_vcbo(QOpenGLBuffer::VertexBuffer);
//    m_vcbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
//    m_vcbo.bind();
//    m_vcbo.allocate(vertexColors, 9 * sizeof(float));
//    m_program.enableAttributeArray("color"); //this labels an attribute &quot;color&quot;
//    //that points to the memory slot from the last buffer allocate()
//    //the color attribute is an input to our vertex shader
//    m_program.setAttributeBuffer("color", GL_FLOAT, 0, 3);

//    glDrawElements(GL_TRIANGLES, 34, GL_UNSIGNED_SHORT, 0);

//    // Release (unbind) all
//    m_vvbo.release();
//    m_vcbo.release();
//    m_vao.release();
//    m_program.release();
    quintptr offset = 0;
    m_vao1->bind();
    int color = m_program.attributeLocation("color");
    m_program.setAttributeValue(color, 1.0f);
    glDrawArrays(GL_TRIANGLES, 0, m_shape->numVertices());

    m_program.setAttributeValue(color, 0.0f);
    glDrawArrays(GL_LINES, 0, m_shape->numVertices());

//    QMatrix4x4 matrix2;
//    matrix2.translate(-2.0, 0.0, -5.0);
//    matrix2.rotate(rotation);

////    // Set modelview-projection matrix
//    m_program.setUniformValue("mvp_matrix", projection * matrix2);

//    m_vao2->bind();
//    color = m_program.attributeLocation("color");
//    m_program.setAttributeValue(color, 1.0f);
//    glDrawArrays(GL_TRIANGLES, 0, m_shape2->numVertices());

//    m_program.setAttributeValue(color, 0.0f);
//    glDrawArrays(GL_LINES, 0, m_shape2->numVertices());

//    // Draw cube geometry
    //geometries->drawCubeGeometry(&m_program, projection, rotation);

    //geometries->drawCubeGeoTwo(&program);
}
