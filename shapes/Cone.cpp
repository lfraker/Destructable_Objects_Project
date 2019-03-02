#include "Cone.h"

#define PI 3.14159265
#define INTERNAL_POINTS 5

Cone::Cone(int p1, int p2, int radius)
    : Shape(p1, p2, INTERNAL_POINTS)
{
    m_radius = radius;
    computeTriangles();
}

Cone::~Cone()
{

}

void Cone::computeTriangles()
{
    int tris = ((m_param1 * m_param2) * 2);
    //int triVerts = ((tris * 3) * 6) * 2;
    int triVerts = (tris * 6) * 2;
    //m_triangles = new QVector3D[triVerts];
    m_triangles = new Triangle[triVerts];
    int ctr = 0;

    //Cap Top
    float radiInc = (m_radius/m_param1);
    for (int rCount = 0; rCount < m_param2; ++rCount) {
        for (int radi = 0; radi < m_param1; ++radi) {
            float radiDecr = m_radius - (radiInc * radi);
            float rad = ((PI * 2.0f) * rCount)/m_param2;
            float radP = ((PI * 2.0f) * (rCount + 1))/m_param2;

            //Top Right
            float height = m_radius - 0.5f;

            QVector3D vert1 = QVector3D(radiDecr * cos(rad), -height, radiDecr * sin(rad));
            QVector3D norm1 = QVector3D(0.0f, -1.0f, 0.0f);


            //Top left

            QVector3D vert2 = QVector3D(radiDecr * cos(radP), -height, radiDecr * sin(radP));
            QVector3D norm2 = QVector3D(0.0f, -1.0f, 0.0f);

            //Bottom left

            QVector3D vert3 = QVector3D((radiDecr - radiInc) * cos(radP), -height, (radiDecr - radiInc) * sin(radP));
            QVector3D norm3 = QVector3D(0.0f, -1.0f, 0.0f);


            //Top Right

            QVector3D vert4 = QVector3D(radiDecr * cos(rad),  -height, radiDecr * sin(rad));
            QVector3D norm4 = QVector3D(0.0f, -1.0f, 0.0f);


            //bottom left

            QVector3D vert5 = QVector3D((radiDecr - radiInc) * cos(radP),-height, (radiDecr - radiInc) * sin(radP));
            QVector3D norm5 = QVector3D(0.0f, -1.0f, 0.0f);

            //Bottom right

            QVector3D vert6 = QVector3D((radiDecr - radiInc) * cos(rad), -height, (radiDecr - radiInc) * sin(rad));
            QVector3D norm6 = QVector3D(0.0f, -1.0f, 0.0f);

            Triangle one = Triangle(vert4, vert5, vert6);
            Triangle two = Triangle(vert1, vert2, vert3);
            m_triangles[ctr] = one;
            ctr++;
            m_triangles[ctr] = two;
            ctr++;

//            m_triangles[ctr] = vert4;
//            ctr++;
//            m_triangles[ctr] = vert5;
//            ctr++;
//            m_triangles[ctr] = vert6;
//            ctr++;
//            m_triangles[ctr] = vert1;
//            ctr++;
//            m_triangles[ctr] = vert2;
//            ctr++;
//            m_triangles[ctr] = vert3;
//            ctr++;

        }
    }

    for (int rCount = 0; rCount < m_param2; ++rCount) {
        for (int h = 0; h < m_param1; ++h) {
            float radiDecr = m_radius - (radiInc * h);
            float rad = ((PI * 2.0f) * rCount)/m_param2;
            float radP = ((PI * 2.0f) * (rCount + 1))/m_param2;
            float currHeight = (((1.0/m_param1) * h) - 0.5f);
            float heightDiff = (1.0/m_param1);
            float xzNorm = 2.0f/sqrt(5.0);
            float yNorm = 1.0f/sqrt(5.0);

            //Top Right

            QVector3D vert1 = QVector3D(radiDecr * cos(rad), currHeight, radiDecr * sin(rad));
            QVector3D norm1 = QVector3D(cos(rad) * xzNorm, yNorm, sin(rad) * xzNorm);


            //Top left

            QVector3D vert2 = QVector3D(radiDecr * cos(radP), currHeight, radiDecr * sin(radP));
            QVector3D norm2 = QVector3D(cos(radP) * xzNorm, yNorm, sin(radP) * xzNorm);

            //Bottom left

            QVector3D vert3 = QVector3D((radiDecr - radiInc) * cos(radP), (currHeight + heightDiff), (radiDecr - radiInc) * sin(radP));
            QVector3D norm3 = QVector3D(cos(radP) * xzNorm, yNorm, sin(radP) * xzNorm);


            //Top Right

            QVector3D vert4 = QVector3D(radiDecr * cos(rad), currHeight, radiDecr * sin(rad));
            QVector3D norm4 = QVector3D(cos(rad) * xzNorm, yNorm, sin(rad) * xzNorm);


            //Bottom left

            QVector3D vert5 = QVector3D((radiDecr - radiInc) * cos(radP), (currHeight + heightDiff), (radiDecr - radiInc) * sin(radP));
            QVector3D norm5 = QVector3D(cos(radP) * xzNorm, yNorm, sin(radP) * xzNorm);

            //Bottom right

            QVector3D vert6 = QVector3D((radiDecr - radiInc) * cos(rad), (currHeight + heightDiff), (radiDecr - radiInc) * sin(rad));
            QVector3D norm6 = QVector3D(cos(rad) * xzNorm, yNorm, sin(rad) * xzNorm);

            if (h == (m_param1 - 1)) {
                float radN = (rad + ((radP - rad)/2.0f));
                norm3 = QVector3D(cos(radN) * xzNorm, yNorm, sin(radN) * xzNorm);
                norm5 = QVector3D(cos(radN) * xzNorm, yNorm, sin(radN) * xzNorm);
                norm6 = QVector3D(cos(radN) * xzNorm, yNorm, sin(radN) * xzNorm);
            }

            Triangle one = Triangle(vert4, vert6, vert5);
            Triangle two = Triangle(vert1, vert3, vert2);
            m_triangles[ctr] = one;
            ctr++;
            m_triangles[ctr] = two;
            ctr++;

//            m_triangles[ctr] = vert4;
//            ctr++;
//            m_triangles[ctr] = vert6;
//            ctr++;
//            m_triangles[ctr] = vert5;
//            ctr++;
//            m_triangles[ctr] = vert1;
//            ctr++;
//            m_triangles[ctr] = vert3;
//            ctr++;
//            m_triangles[ctr] = vert2;
//            ctr++;

        }
    }

    m_numTris = ctr;
    genVecs();
}
