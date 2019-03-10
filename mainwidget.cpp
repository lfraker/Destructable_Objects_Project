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
    QOpenGLWidget(parent)
    //geometries(0),
    //texture(0),
    //angularSpeed(0),
    //m_vao1(new QOpenGLVertexArrayObject),
    //m_vao2(new QOpenGLVertexArrayObject)
{
}

MainWidget::~MainWidget()
{
    //TODO: delete array of shapes
    // Make sure the context is current when deleting the texture
    // and the buffers.
    deleteShapeResources();
    makeCurrent();
    delete texture;
    //delete geometries;
    delete m_shape; // TODO occasional segfault here
    doneCurrent();
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}


void MainWidget::destructObj(int depth) {
    Shape ** temp_shapes = Voronoi::split(m_shapes[0], depth);
    deleteShapeResources();
    m_numShapes = static_cast<int>(pow(2, depth));
    m_shapes = temp_shapes;
    resetGl();
    update();
}

void MainWidget::reset() {
    mousePressPosition = QVector2D(0.0, 0.0);
    m_camRotationAxis = QVector3D(0.0, 0.0, 0.0);
    m_camAngularSpeed = 0;
    m_camRotation = QQuaternion();
    m_camZoom = QVector3D(1.0, 1.0, 1.0);
    m_camTranslate = QVector3D(0.0, 0.0, 0.0);
    refreshShape();
}

void MainWidget::changeShapeType(ShapeType newType) {
    m_shapeType = newType;
    refreshShape();
}

void MainWidget::zoom(int zoomVal) {
    m_camZoom.setX(m_camZoom.x() + (zoomVal * m_camZoomFactor));
    m_camZoom.setY(m_camZoom.y() + (zoomVal * m_camZoomFactor));
    m_camZoom.setZ(m_camZoom.z() + (zoomVal * m_camZoomFactor));
    update();
}

void MainWidget::pan(int leftRight, int upDown) {
    m_camTranslate.setX(m_camTranslate.x() + (leftRight * m_camTranslateFactor));
    m_camTranslate.setY(m_camTranslate.y() + (upDown * m_camTranslateFactor));
    update();
}

void MainWidget::advanceSplitIncr() {
    for (int i = 0; i < m_numShapes; i++) {
        m_shapes[i]->m_direction += (m_shapes[i]->m_direction * 0.1);
    }
    update();
}

void MainWidget::deleteShapeResources() {
    if (m_shapes != NULL) {
        for (int i = 0; i < m_numShapes; i++) {
            m_vaos[i]->release();
            m_positionBuffers[i]->release();
            m_vaos[i]->destroy();
            m_positionBuffers[i]->destroy();
            delete m_vaos[i];
            delete m_positionBuffers[i];
            delete m_shapes[i];
        }

        delete [] m_shapes;
    }

    m_shapes = NULL;

    if (m_vaos != NULL) {
        delete [] m_vaos;
    }

    m_vaos = NULL;

    if (m_positionBuffers != NULL) {
        delete [] m_positionBuffers;
    }

    m_positionBuffers = NULL;

    if (m_transforms != NULL) {
        delete [] m_transforms;
    }

    m_transforms = NULL;
}

void MainWidget::pauseResumeSplit(bool pause) {
    m_pauseSplit = pause;
}


void MainWidget::refreshShape() {
    deleteShapeResources();
    Shape * temp_shape;
    switch (m_shapeType) {
        case SphereType:
            temp_shape = new Sphere(p1, p2, 1);
            break;
        case CylinderType:
            temp_shape = new Cylinder(p1, p2, 1);
            break;
        case ConeType:
            temp_shape = new Cone(p1, p2, 1);
            break;
        case CubeType:
            temp_shape = new Cube(p1, p2);
            break;
    }

    m_numShapes = 1;
    m_shapes = new Shape* [m_numShapes] { temp_shape };

    resetGl();
    update();
}

void MainWidget::resetGl() {
    this->makeCurrent();
    m_vaos = new QOpenGLVertexArrayObject * [m_numShapes];
    m_positionBuffers = new QOpenGLBuffer * [m_numShapes];
    m_transforms = new TransformDetails [m_numShapes];

    for (int i = 0; i < m_numShapes; i++) {
        QOpenGLVertexArrayObject * vao = new QOpenGLVertexArrayObject(this);
        QOpenGLBuffer * posBuff = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        vao->create();
        vao->bind();

        posBuff->create();
        posBuff->bind();
        posBuff->setUsagePattern(QOpenGLBuffer::DynamicDraw);
        posBuff->allocate(m_shapes[i]->getVecs(), m_shapes[i]->numVertices() * sizeof(QVector3D) );
        m_program.enableAttributeArray("a_position");
        m_program.setAttributeBuffer( "a_position", GL_FLOAT, 0, 3, sizeof(QVector3D));
        posBuff->release(QOpenGLBuffer::VertexBuffer);
        vao->release();
        m_vaos[i] = vao;
        m_positionBuffers[i] = posBuff;
        m_transforms[i] = TransformDetails();
        m_transforms[i].m_shapeTranslate = QVector3D(0.0, 0.0, 0.0);

    }
}

void MainWidget::sliderChanged(bool param1, int val) {

    if (param1){
        p1 = val;
    }
    else {
        p2 = val;
    }

    refreshShape();
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
    m_camRotationAxis = (m_camRotationAxis * m_camAngularSpeed + n * acc).normalized();

    // Increase angular speed
    m_camAngularSpeed += acc;
}

void MainWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    m_camAngularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (m_camAngularSpeed < 0.01) {
        m_camAngularSpeed = 0.0;
    } else {
        // Update rotation
        m_camRotation = QQuaternion::fromAxisAndAngle(m_camRotationAxis, m_camAngularSpeed) * m_camRotation;

        // Request an update
        update();
    }
}


void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();
    this->makeCurrent();
    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    // Enable point size adjustment
    //glEnable(GL_PROGRAM_POINT_SIZE);

    refreshShape();

    // Repeat for buffers of normals, texture coordinates,
    // tangents, ...

    // Setup VBOs and IBO for next object

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

void MainWidget::initShaders()
{
    // Init point size
    //glPointSize(10);

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
    const qreal zNear = 1.0, zFar = 30.0, fov = 45.0;
    this->makeCurrent();
    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void MainWidget::paintGL()
{
    if (!m_pauseSplit) {
        for (int i = 0; i < m_numShapes; i++) {
            m_shapes[i]->m_direction += (m_shapes[i]->m_direction * 0.001);
        }
    }

    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->makeCurrent();
    texture->bind();

    for (int i = 0; i < m_numShapes; i++) {

        // Calculate model view transformation
        QMatrix4x4 matrix;
        matrix.translate(0.0, 0.0, -10.0);
        matrix.translate(m_camTranslate);
        matrix.scale(m_camZoom);
        matrix.rotate(m_camRotation);
        matrix.translate(m_shapes[i]->m_direction);

        // Set modelview-projection matrix
        m_program.setUniformValue("mvp_matrix", projection * matrix);

        // Use texture unit 0 which contains cube.png
        m_program.setUniformValue("texture", 0);

        quintptr offset = 0;

        m_vaos[i]->bind();
        m_positionBuffers[i]->bind();
        int color = m_program.attributeLocation("color");
        m_program.setAttributeValue(color, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, m_shapes[i]->numVertices());

        //int points_count = 2;
        //QVector3D * points = Voronoi::generatePoints(m_shapes[i]->getTris(), 2);
        //glDrawArrays(GL_POINTS, 0, 2);

        m_program.setAttributeValue(color, 0.0f);
        glDrawArrays(GL_LINES, 0, m_shapes[i]->numVertices());
        glFinish();
        m_vaos[i]->release();
    }
    glFlush();
}
