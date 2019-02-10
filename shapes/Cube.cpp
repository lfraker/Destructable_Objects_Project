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
    int triVerts = (((tris * 6) * 3) * 6);
    int ctr = 0;

    m_vertexData = new QVector3D[triVerts];

    double side = (1.0/m_param1);





//    Loops for +- faces on the z axis
    for (double sign = -1.0; sign < 2.0; sign += 2.0) {
        for (double y = 0.5; y > -0.5; y -= side) {
            for (double x = -0.5; x < 0.5; x += side) {


                //Top Right

                QVector3D vert1 = QVector3D(sign * (x + side), y, sign * 0.5);
                QVector3D norm1 = QVector3D(0.0, 0.0, sign * 1.0);




                //Top left

                QVector3D vert2 = QVector3D(sign * x, y, sign * 0.5);
                QVector3D norm2 = QVector3D(0.0, 0.0, sign * 1.0);

                //Bottom left

                QVector3D vert3 = QVector3D(sign * x, (y - side), sign * 0.5);
                QVector3D norm3 = QVector3D(0.0, 0.0, sign * 1.0);



                //Top Right

                QVector3D vert4 = QVector3D( sign * (x + side), y, sign * 0.5);
                QVector3D norm4 = QVector3D(0.0, 0.0, sign * 1.0);


                //bottom left

                QVector3D vert5 = QVector3D(sign * x, (y - side), sign * 0.5);
                QVector3D norm5 = QVector3D(0.0, 0.0, sign * 1.0);

                //Bottom right

                QVector3D vert6 = QVector3D(sign * (x + side), (y - side), sign * 0.5);
                QVector3D norm6 = QVector3D(0.0, 0.0, sign * 1.0);

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
        }
    }

//    Loops for +- faces on the y axis
    for (double sign = -1.0; sign < 2.0; sign += 2.0) {
        for (double z = 0.5; z > -0.5; z -= side) {
            for (double x = 0.5; x > -0.5; x -= side) {
                //First Triangle

                //Top Right

                QVector3D vert1 = QVector3D(sign * (x - side), sign * 0.5, z);
                QVector3D norm1 = QVector3D(0.0, sign * 1.0, 0.0);




                //Top left

                QVector3D vert2 = QVector3D(sign * x, sign * 0.5, z);
                QVector3D norm2 = QVector3D(0.0, sign * 1.0, 0.0);

                //Bottom left

                QVector3D vert3 = QVector3D(sign * x, sign * 0.5,(z - side));
                QVector3D norm3 = QVector3D(0.0, sign * 1.0, 0.0);



                //Top Right

                QVector3D vert4 = QVector3D( sign * (x - side), sign * 0.5, z);
                QVector3D norm4 = QVector3D(0.0, sign * 1.0, 0.0);


                //bottom left

                QVector3D vert5 = QVector3D(sign * x, sign * 0.5, (z - side));
                QVector3D norm5 = QVector3D(0.0, sign * 1.0, 0.0);

                //Bottom right

                QVector3D vert6 = QVector3D(sign * (x - side), sign * 0.5, (z - side));
                QVector3D norm6 = QVector3D(0.0, sign * 1.0, 0.0);

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
        }
    }



    //    Loops for + faces on the x axis
        for (double sign = 1.0; sign > -2.0; sign -= 2.0) {
            for (double y = 0.5; y > -0.5; y -= side) {
                for (double z = -0.5; z < 0.5; z += side) {
                    //First Triangle


                    //Top Right

                    QVector3D vert1 = QVector3D(sign * 0.5, y, sign * (z + side));
                    QVector3D norm1 = QVector3D(sign * 1.0, 0.0, 0.0);




                    //Top left

                    QVector3D vert2 = QVector3D(sign * 0.5, y, sign * z);
                    QVector3D norm2 = QVector3D(sign * 1.0, 0.0, 0.0);

                    //Bottom left

                    QVector3D vert3 = QVector3D(sign * 0.5, (y - side), sign * z);
                    QVector3D norm3 = QVector3D(sign * 1.0, 0.0, 0.0);



                    //Top Right

                    QVector3D vert4 = QVector3D(sign * 0.5, y, sign * (z + side));
                    QVector3D norm4 = QVector3D(sign * 1.0, 0.0, 0.0);


                    //bottom left

                    QVector3D vert5 = QVector3D(sign * 0.5, (y - side), sign * z);
                    QVector3D norm5 = QVector3D(sign * 1.0, 0.0, 0.0);

                    //Bottom right

                    QVector3D vert6 = QVector3D(sign * 0.5, (y - side), sign * (z + side));
                    QVector3D norm6 = QVector3D(sign * 1.0, 0.0, 0.0);

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

     m_numVerts = ctr;

}
