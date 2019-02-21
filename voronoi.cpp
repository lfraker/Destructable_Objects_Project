#include "voronoi.h"

#include "geometryengine.h"
#include "vertexdata.h"

#include <QVector2D>
#include <QVector3D>

static int DEFAULT_POINTS = 5;

Voronoi::Voronoi()
{
}

VertexData * Voronoi::split(VertexData *vertices)
{
    return split(vertices, DEFAULT_POINTS);
}

VertexData * Voronoi::split(VertexData *vertices, int points)
{
    return vertices;
}
