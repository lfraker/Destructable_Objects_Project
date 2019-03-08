QT       += core gui widgets

TARGET = cube
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    shapes/Sphere.cpp \
    shapes/Cube.cpp \
    shapes/Cone.cpp \
    shapes/Cylinder.cpp \
    shapes/Shape.cpp \
    voronoi.cpp

SOURCES += \
    mainwidget.cpp

HEADERS += \
    mainwidget.h \
    mainwindow.h \
    shapes/Shape.h \
    shapes/Sphere.h \
    shapes/Cube.h \
    shapes/Cone.h \
    shapes/Cylinder.h \
    voronoi.h \
    shapes/Torus.h \
    shapes/Triangle.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target


##-------------------------------------------------
##
## Project created by QtCreator 2019-02-04T23:55:35
##
##-------------------------------------------------

#QT       += core gui widgets

#TARGET = cube
#TEMPLATE = app

#SOURCES += main.cpp

#SOURCES += \
#    mainwidget.cpp \
#    geometryengine.cpp

#HEADERS += \
#    mainwidget.h \
#    geometryengine.h

#RESOURCES += \
#    shaders.qrc \
#    textures.qrc

## install
#target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
#INSTALLS += target

## QT       += core gui

## greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

## TARGET = DestructionSimulation
## TEMPLATE = app

## The following define makes your compiler emit warnings if you use
## any feature of Qt which has been marked as deprecated (the exact warnings
## depend on your compiler). Please consult the documentation of the
## deprecated API in order to know how to port your code away from it.
## DEFINES += QT_DEPRECATED_WARNINGS

## You can also make your code fail to compile if you use deprecated APIs.
## In order to do so, uncomment the following line.
## You can also select to disable deprecated APIs only up to a certain version of Qt.
###DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

## CONFIG += c++11

## SOURCES += \
##        main.cpp \
##        mainwidget.cpp

## HEADERS += \
##        mainwidget.h

## Default rules for deployment.
## qnx: target.path = /tmp/$${TARGET}/bin
## else: unix:!android: target.path = /opt/$${TARGET}/bin
## !isEmpty(target.path): INSTALLS += target

#DISTFILES += \
#    fshader.glsl \
#    vshader.glsl

FORMS += \
    mainwindow.ui
