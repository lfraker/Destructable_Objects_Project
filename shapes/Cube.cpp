#include "Cube.h"

Cube::Cube(int p1, int p2)
    : Shape(p1, p2)
{
    computeTriangles();
}

Cube::~Cube()
{

}

void Cube::computeTriangles()
{
    int tris = ((m_param1 * m_param1) * 2);
    //int triVerts = (((tris * 6) * 3) * 6);
    int triVerts = ((tris * 6) * 6);
    int ctr = 0;
    //m_triangles = new QVector3D[triVerts];
    m_triangles = new Triangle[triVerts];
    double length = 1.0;
    double side = ((length * 2.0)/m_param1);
    int num_steps = (int)round((length - (-length))/side);


//    Loops for +- faces on the z axis
    for (double sign = -1.0; sign < 2.0; sign += 2.0) {
        for (int ty = 0; ty < num_steps; ++ty) {
            for (int tx = 0; tx < num_steps; ++tx) {
                double y = length - (ty * side);
                double x = -length + (tx * side);

                //Top Right
                QVector3D vert1 = QVector3D(sign * (x + side), y, sign * length);
                QVector3D norm1 = QVector3D(0.0, 0.0, sign * 1.0);

                //Top left
                QVector3D vert2 = QVector3D(sign * x, y, sign * length);
                QVector3D norm2 = QVector3D(0.0, 0.0, sign * 1.0);

                //Bottom left
                QVector3D vert3 = QVector3D(sign * x, (y - side), sign * length);
                QVector3D norm3 = QVector3D(0.0, 0.0, sign * 1.0);

                //Top Right
                QVector3D vert4 = QVector3D( sign * (x + side), y, sign * length);
                QVector3D norm4 = QVector3D(0.0, 0.0, sign * 1.0);

                //bottom left
                QVector3D vert5 = QVector3D(sign * x, (y - side), sign * length);
                QVector3D norm5 = QVector3D(0.0, 0.0, sign * 1.0);

                //Bottom right
                QVector3D vert6 = QVector3D(sign * (x + side), (y - side), sign * length);
                QVector3D norm6 = QVector3D(0.0, 0.0, sign * 1.0);

                Triangle one = Triangle(vert1, vert2, vert3);
                Triangle two = Triangle(vert4, vert5, vert6);
                m_triangles[ctr] = one;
                ctr++;
                m_triangles[ctr] = two;
                ctr++;

//            m_triangles[ctr] = vert1;
//            ctr++;
//            m_triangles[ctr] = vert2;
//            ctr++;
//            m_triangles[ctr] = vert3;
//            ctr++;
//            m_triangles[ctr] = vert4;
//            ctr++;
//            m_triangles[ctr] = vert5;
//            ctr++;
//            m_triangles[ctr] = vert6;
//            ctr++;
            }
        }
    }

//    Loops for +- faces on the y axis
    for (double sign = -1.0; sign < 2.0; sign += 2.0) {
        for (int tz = 0; tz < num_steps; ++tz) {
            for (int tx = 0; tx < num_steps; ++tx) {
                double z = length - (tz * side);
                double x = length - (tx * side);

                //Top Right
                QVector3D vert1 = QVector3D(sign * (x - side), sign * length, z);
                QVector3D norm1 = QVector3D(0.0, sign * 1.0, 0.0);

                //Top left
                QVector3D vert2 = QVector3D(sign * x, sign * length, z);
                QVector3D norm2 = QVector3D(0.0, sign * 1.0, 0.0);

                //Bottom left
                QVector3D vert3 = QVector3D(sign * x, sign * length,(z - side));
                QVector3D norm3 = QVector3D(0.0, sign * 1.0, 0.0);

                //Top Right
                QVector3D vert4 = QVector3D( sign * (x - side), sign * length, z);
                QVector3D norm4 = QVector3D(0.0, sign * 1.0, 0.0);

                //bottom left
                QVector3D vert5 = QVector3D(sign * x, sign * length, (z - side));
                QVector3D norm5 = QVector3D(0.0, sign * 1.0, 0.0);

                //Bottom right
                QVector3D vert6 = QVector3D(sign * (x - side), sign * length, (z - side));
                QVector3D norm6 = QVector3D(0.0, sign * 1.0, 0.0);

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
    }


    //    Loops for + faces on the x axis
        for (double sign = 1.0; sign > -2.0; sign -= 2.0) {
            for (int ty = 0; ty < num_steps; ++ty) {
                for (int tz = 0; tz < num_steps; ++tz) {
                    double y = length - (ty * side);
                    double z = -length + (tz * side);

                    //Top Right
                    QVector3D vert1 = QVector3D(sign * length, y, sign * (z + side));
                    QVector3D norm1 = QVector3D(sign * 1.0, 0.0, 0.0);

                    //Top left
                    QVector3D vert2 = QVector3D(sign * length, y, sign * z);
                    QVector3D norm2 = QVector3D(sign * 1.0, 0.0, 0.0);

                    //Bottom left
                    QVector3D vert3 = QVector3D(sign * length, (y - side), sign * z);
                    QVector3D norm3 = QVector3D(sign * 1.0, 0.0, 0.0);



                    //Top Right
                    QVector3D vert4 = QVector3D(sign * length, y, sign * (z + side));
                    QVector3D norm4 = QVector3D(sign * 1.0, 0.0, 0.0);


                    //bottom left
                    QVector3D vert5 = QVector3D(sign * length, (y - side), sign * z);
                    QVector3D norm5 = QVector3D(sign * 1.0, 0.0, 0.0);

                    //Bottom right
                    QVector3D vert6 = QVector3D(sign * length, (y - side), sign * (z + side));
                    QVector3D norm6 = QVector3D(sign * 1.0, 0.0, 0.0);

                    Triangle one = Triangle(vert1, vert3, vert2);
                    Triangle two = Triangle(vert4, vert6, vert5);
                    m_triangles[ctr] = one;
                    ctr++;
                    m_triangles[ctr] = two;
                    ctr++;

//                  m_triangles[ctr] = vert1;
//                  ctr++;
//                  m_triangles[ctr] = vert3;
//                  ctr++;
//                  m_triangles[ctr] = vert2;
//                  ctr++;
//                  m_triangles[ctr] = vert4;
//                  ctr++;
//                  m_triangles[ctr] = vert6;
//                  ctr++;
//                  m_triangles[ctr] = vert5;
//                  ctr++;
                }
            }
        }

    m_numTris = ctr;
    genVecs();
}
