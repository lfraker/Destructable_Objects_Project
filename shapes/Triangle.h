#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QVector3D>

struct Triangle {
    QVector3D m_left;
    QVector3D m_right;
    QVector3D m_top;

    Triangle(QVector3D left, QVector3D right, QVector3D top)
    {
        m_left = left;
        m_right = right;
        m_top = top;
    }

    Triangle() { }

    int addElements(QVector3D verts[], int startInd)
    {
        verts[startInd] = m_left;
        startInd++;
        verts[startInd] = m_right;
        startInd++;
        verts[startInd] = m_top;
        startInd++;
        return startInd;
    }
};

#endif // TRIANGLE_H
