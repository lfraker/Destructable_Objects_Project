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

    float side = (1.0f/m_param1);





//    Loops for +- faces on the z axis
    for (float sign = -1.0; sign < 2.0f; sign += 2.0f) {
        for (float y = 0.5f; y > -0.4999f; y -= side) {
            for (float x = -0.5f; x < 0.4999f; x += side) {


                //Top Right

                QVector3D vert1 = QVector3D(sign * (x + side), y, sign * 0.5f);
                QVector3D norm1 = QVector3D(0.0f, 0.0f, sign * 1.0);




                //Top left

                QVector3D vert2 = QVector3D(sign * x, y, sign * 0.5f);
                QVector3D norm2 = QVector3D(0.0f, 0.0f, sign * 1.0);

                //Bottom left

                QVector3D vert3 = QVector3D(sign * x, (y - side), sign * 0.5f);
                QVector3D norm3 = QVector3D(0.0f, 0.0f, sign * 1.0);



                //Top Right

                QVector3D vert4 = QVector3D( sign * (x + side), y, sign * 0.5f);
                QVector3D norm4 = QVector3D(0.0f, 0.0f, sign * 1.0);


                //bottom left

                QVector3D vert5 = QVector3D(sign * x, (y - side), sign * 0.5f);
                QVector3D norm5 = QVector3D(0.0f, 0.0f, sign * 1.0);

                //Bottom right

                QVector3D vert6 = QVector3D(sign * (x + side), (y - side), sign * 0.5f);
                QVector3D norm6 = QVector3D(0.0f, 0.0f, sign * 1.0);

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
    for (float sign = -1.0; sign < 2.0f; sign += 2.0f) {
        for (float z = 0.5f; z > -0.4999f; z -= side) {
            for (float x = 0.5f; x > -0.4999f; x -= side) {
                //First Triangle

                //Top Right

                QVector3D vert1 = QVector3D(sign * (x - side), sign * 0.5f, z);
                QVector3D norm1 = QVector3D(0.0f, sign * 1.0f, 0.0f);




                //Top left

                QVector3D vert2 = QVector3D(sign * x, sign * 0.5f, z);
                QVector3D norm2 = QVector3D(0.0f, sign * 1.0f, 0.0f);

                //Bottom left

                QVector3D vert3 = QVector3D(sign * x, sign * 0.5f,(z - side));
                QVector3D norm3 = QVector3D(0.0f, sign * 1.0f, 0.0f);



                //Top Right

                QVector3D vert4 = QVector3D( sign * (x - side), sign * 0.5f, z);
                QVector3D norm4 = QVector3D(0.0f, sign * 1.0f, 0.0f);


                //bottom left

                QVector3D vert5 = QVector3D(sign * x, sign * 0.5f, (z - side));
                QVector3D norm5 = QVector3D(0.0f, sign * 1.0f, 0.0f);

                //Bottom right

                QVector3D vert6 = QVector3D(sign * (x - side), sign * 0.5f, (z - side));
                QVector3D norm6 = QVector3D(0.0f, sign * 1.0f, 0.0f);

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
        for (float sign = 1.0; sign > -2.0f; sign -= 2.0f) {
            for (float y = 0.5f; y > -0.4999f; y -= side) {
                for (float z = -0.5f; z < 0.4999f; z += side) {
                    //First Triangle



                    //Top Right

                    QVector3D vert1 = QVector3D(sign * -0.5f, y, sign * (z + side));
                    QVector3D norm1 = QVector3D(sign * -1.0f, 0.0f, 0.0f);




                    //Top left

                    QVector3D vert2 = QVector3D(sign * -0.5f, y, sign * z);
                    QVector3D norm2 = QVector3D(sign * -1.0f, 0.0f, 0.0f);

                    //Bottom left

                    QVector3D vert3 = QVector3D(sign * -0.5f, (y - side), sign * z);
                    QVector3D norm3 = QVector3D(sign * -1.0f, 0.0f, 0.0f);



                    //Top Right

                    QVector3D vert4 = QVector3D(sign * -0.5f, y, sign * (z + side));
                    QVector3D norm4 = QVector3D(sign * -1.0f, 0.0f, 0.0f);


                    //bottom left

                    QVector3D vert5 = QVector3D(sign * -0.5f, (y - side), sign * z);
                    QVector3D norm5 = QVector3D(sign * -1.0f, 0.0f, 0.0f);

                    //Bottom right

                    QVector3D vert6 = QVector3D(sign * -0.5f, (y - side), sign * (z + side));
                    QVector3D norm6 = QVector3D(sign * -1.0f, 0.0f, 0.0f);

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

     m_numVerts = ctr;

}
