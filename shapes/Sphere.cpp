#include "Sphere.h"


#define PI 3.14159265


Sphere::Sphere(int p1, int p2, int radius)
    : Shape(p1, p2)
{
    m_radius = radius;
    computeTriangles();
}

Sphere::~Sphere()
{

}

void Sphere::computeTriangles()
{
    int tris = ((m_param1 * m_param2) * 2);
    //int triVerts = ((tris * 3) * 6);
    int triVerts = (tris * 6);
    int ctr = 0;
    //m_triangles = new QVector3D[triVerts];
    m_triangles = new Triangle[triVerts];

    for (int rCount = 0; rCount < m_param2; ++rCount) {
        for (int hCount = 0; hCount < m_param1; ++hCount) {
            float rad = ((PI * 2.0f) * rCount)/m_param2;
            float radP = ((PI * 2.0f) * (rCount + 1))/m_param2;
            float hrad = ((PI * 2.0f) * hCount)/(m_param1 * 2);
            float hradP = ((PI * 2.0f) * (hCount + 1))/(m_param1 * 2);


            //Top Right

            QVector3D vert1 = QVector3D(m_radius * cos(rad) * sin(hrad), m_radius * cos(hrad), m_radius * sin(rad) * sin(hrad));
            float x1 = m_radius * cos(rad) * sin(hrad);
            float y1 = m_radius * cos(hrad);
            float z1 = m_radius * sin(rad) * sin(hrad);
            float mag1 = sqrt((x1 * x1) + (y1 * y1) + (z1 * z1));
            //QVector3D norm1 = QVector3D(x1/mag1, y1/mag1, z1/mag1);


            //Top left

            QVector3D vert2 = QVector3D(m_radius * cos(radP) * sin(hrad), m_radius * cos(hrad), m_radius * sin(radP) * sin(hrad));
            float x2 = m_radius * cos(radP) * sin(hrad);
            float y2 = m_radius * cos(hrad);
            float z2 = m_radius * sin(radP) * sin(hrad);
            float mag2 = sqrt((x2 * x2) + (y2 * y2) + (z2 * z2));
            //QVector3D norm2 = QVector3D(x2/mag2, y2/mag2, z2/mag2);

            //Bottom left

            QVector3D vert3 = QVector3D(m_radius * cos(radP) * sin(hradP), m_radius * cos(hradP), m_radius * sin(radP) * sin(hradP));
            float x3 = m_radius * cos(radP) * sin(hradP);
            float y3 = m_radius * cos(hradP);
            float z3 = m_radius * sin(radP) * sin(hradP);
            float mag3 = sqrt((x3 * x3) + (y3 * y3) + (z3 * z3));
            //QVector3D norm3 = QVector3D(x3/mag3, y3/mag3, z3/mag3);


            //Top Right

            QVector3D vert4 = QVector3D(m_radius * cos(rad) * sin(hrad), m_radius * cos(hrad), m_radius * sin(rad) * sin(hrad));
            //QVector3D norm4 = QVector3D(x1/mag1, y1/mag1, z1/mag1);


            //Bottom left

            QVector3D vert5 = QVector3D(m_radius * cos(radP) * sin(hradP), m_radius * cos(hradP), m_radius * sin(radP) * sin(hradP));
            //QVector3D norm5 = QVector3D(x3/mag3, y3/mag3, z3/mag3);

            //Bottom right

            QVector3D vert6 = QVector3D(m_radius * cos(rad) * sin(hradP), m_radius * cos(hradP), m_radius * sin(rad) * sin(hradP));
            float x4 = m_radius * cos(rad) * sin(hradP);
            float y4 = m_radius * cos(hradP);
            float z4 = m_radius * sin(rad) * sin(hradP);
            float mag4 = sqrt((x4 * x4) + (y4 * y4) + (z4 * z4));
            //QVector3D norm6 = QVector3D(x4/mag4, y4/mag4, z4/mag4);

//            m_triangles[ctr] = vert1.x();
//            ctr++;
//            m_triangles[ctr] = vert1.y();
//            ctr++;
//            m_triangles[ctr] = vert1.z();
//            ctr++;

//            m_triangles[ctr] = vert2.x();
//            ctr++;
//            m_triangles[ctr] = vert2.y();
//            ctr++;
//            m_triangles[ctr] = vert2.z();
//            ctr++;

//            m_triangles[ctr] = vert3.x();
//            ctr++;
//            m_triangles[ctr] = vert3.y();
//            ctr++;
//            m_triangles[ctr] = vert3.z();
//            ctr++;

//            m_triangles[ctr] = vert4.x();
//            ctr++;
//            m_triangles[ctr] = vert4.y();
//            ctr++;
//            m_triangles[ctr] = vert4.z();
//            ctr++;

//            m_triangles[ctr] = vert5.x();
//            ctr++;
//            m_triangles[ctr] = vert5.y();
//            ctr++;
//            m_triangles[ctr] = vert5.z();
//            ctr++;

//            m_triangles[ctr] = vert6.x();
//            ctr++;
//            m_triangles[ctr] = vert6.y();
//            ctr++;
//            m_triangles[ctr] = vert6.z();
//            ctr++;

            Triangle one = Triangle(vert1, vert2, vert3);
            Triangle two = Triangle(vert4, vert5, vert6);
            m_triangles[ctr] = one;
            ctr++;
            m_triangles[ctr] = two;
            ctr++;

//              m_triangles[ctr] = vert1;
//              ctr++;
//              m_triangles[ctr] = vert2;
//              ctr++;
//              m_triangles[ctr] = vert3;
//              ctr++;
//              m_triangles[ctr] = vert4;
//              ctr++;
//              m_triangles[ctr] = vert5;
//              ctr++;
//              m_triangles[ctr] = vert6;
//              ctr++;
        }
    }

    m_numTris = ctr;
    genVecs();
}


