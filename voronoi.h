#ifndef VORONOI_H
#define VORONOI_H

#include "vertexdata.h"
#include <QOpenGLFunctions>

class Voronoi
{
public:
    Voronoi();

    VertexData * split(VertexData *vertices);
    VertexData * split(VertexData *vertices, int points);
};

#endif // VORONOI_H
