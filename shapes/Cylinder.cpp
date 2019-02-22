#include "Cylinder.h"
#include <cmath>

#define PI 3.14159265

Cylinder::Cylinder(int p1, int p2, int radius)
    : Shape(p1, p2)
{
    m_radius = radius;
    computeTriangles();
}

Cylinder::~Cylinder()
{


}

void Cylinder::computeTriangles()
{
    //delete[] m_vertexData;
    float height = 1.0f/m_param1;

    int tris = ((m_param1 * m_param2) * 2);
    int triVerts = ((tris * 3) * 6) * 3;
    m_vertexData = new QVector3D[triVerts];
    int ctr = 0;


//
    //Cap Top
    float radiInc = (m_radius/m_param1);
    for (float sign = -1; sign < 2.0f; sign += 2.0f) {
        for (int rCount = 0; rCount < m_param2; ++rCount) {
            for (int radi = 0; radi < m_param1; ++radi) {
                float radiDecr = m_radius - (radiInc * radi);
                float rad = ((PI * 2.0f) * rCount)/m_param2;
                float radP = ((PI * 2.0f) * (rCount + 1))/m_param2;

                //Top Right

                QVector3D vert1 = QVector3D(radiDecr * cos(rad), (sign * m_radius), radiDecr * sin(rad));
                QVector3D norm1 = QVector3D(0.0f, (sign * 1.0f), 0.0f);


                //Top left

                QVector3D vert2 = QVector3D(radiDecr * cos(radP), (sign * m_radius), radiDecr * sin(radP));
                QVector3D norm2 = QVector3D(0.0f, (sign * 1.0f), 0.0f);

                //Bottom left

                QVector3D vert3 = QVector3D((radiDecr - radiInc) * cos(radP), (sign * m_radius), (radiDecr - radiInc) * sin(radP));
                QVector3D norm3 = QVector3D(0.0f, (sign * 1.0f), 0.0f);


                //Top Right

                QVector3D vert4 = QVector3D(radiDecr * cos(rad), (sign * m_radius), radiDecr * sin(rad));
                QVector3D norm4 = QVector3D(0.0f, (sign * 1.0f), 0.0f);


                //bottom left

                QVector3D vert5 = QVector3D((radiDecr - radiInc) * cos(radP), (sign * m_radius), (radiDecr - radiInc) * sin(radP));
                QVector3D norm5 = QVector3D(0.0f, (sign * 1.0f), 0.0f);

                //Bottom right

                QVector3D vert6 = QVector3D((radiDecr - radiInc) * cos(rad), (sign * m_radius), (radiDecr - radiInc) * sin(rad));
                QVector3D norm6 = QVector3D(0.0f, (sign * 1.0f), 0.0f);

                if (sign < 0.0f) {
                    m_vertexData[ctr] = vert1;
                    ctr++;
                    m_vertexData[ctr] = vert2;
                    ctr++;
                    m_vertexData[ctr] = vert3;
                    ctr++;
                    m_vertexData[ctr] = vert4;
                    ctr++;
                    m_vertexData[ctr] = vert5;
                    ctr++;
                    m_vertexData[ctr] = vert6;
                    ctr++;
                }
                else {
                    m_vertexData[ctr] = vert1;
                    ctr++;
                    m_vertexData[ctr] = vert3;
                    ctr++;
                    m_vertexData[ctr] = vert2;
                    ctr++;
                    m_vertexData[ctr] = vert4;
                    ctr++;
                    m_vertexData[ctr] = vert6;
                    ctr++;
                    m_vertexData[ctr] = vert5;
                    ctr++;
                }

            }
        }
    }

    for (int rCount = 0; rCount < m_param2; ++rCount) {
        for (float y = m_radius; y >= -m_radius; y -= height) {
            float hDiff = (y - height);
            float sRrad = m_radius * sin(((PI * 2.0f) * rCount)/m_param2);
            float sRradP = m_radius * sin(((PI * 2.0f) * (rCount + 1))/m_param2);
            float cRrad = m_radius * cos(((PI * 2.0f) * rCount)/m_param2);
            float cRradP = m_radius * cos(((PI * 2.0f) * (rCount + 1))/m_param2);

            //Top Right

            QVector3D vert1 = QVector3D(cRradP, y, sRradP);
            QVector3D norm1 = QVector3D(2.0f * cRradP, 0.0f, 2.0f * sRradP);


            //Top left

            QVector3D vert2 = QVector3D(cRrad, y, sRrad);
            QVector3D norm2 = QVector3D(2.0f * cRrad, 0.0f, 2.0f * sRrad);

            //Bottom left

            QVector3D vert3 = QVector3D(cRrad, hDiff, sRrad);
            QVector3D norm3 = QVector3D(2.0f * cRrad, 0.0f, 2.0f * sRrad);


            //Top Right

            QVector3D vert4 = QVector3D(cRradP, y, sRradP);
            QVector3D norm4 = QVector3D(2.0f * cRradP, 0.0f, 2.0f * sRradP);


            //bottom left

            QVector3D vert5 = QVector3D(cRrad, hDiff, sRrad);
            QVector3D norm5 = QVector3D(2.0f * cRrad, 0.0f, 2.0f * sRrad);

            //Bottom right

            QVector3D vert6 = QVector3D(cRradP, hDiff, sRradP);
            QVector3D norm6 = QVector3D(2.0f * cRradP, 0.0f, 2.0f * sRradP);

            m_vertexData[ctr] = vert1;
            ctr++;
            m_vertexData[ctr] = vert3;
            ctr++;
            m_vertexData[ctr] = vert2;
            ctr++;
            m_vertexData[ctr] = vert4;
            ctr++;
            m_vertexData[ctr] = vert6;
            ctr++;
            m_vertexData[ctr] = vert5;
            ctr++;
        }

        m_numVerts = ctr;
}






}

