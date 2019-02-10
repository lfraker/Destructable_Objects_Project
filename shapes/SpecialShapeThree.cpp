#include "SpecialShapeThree.h"
#include <cmath>

#define PI 3.14159265



SpecialShapeThree::SpecialShapeThree(int p1, int p2)
    : Shape(p1, p2)
{
    computeTriangles();
}

SpecialShapeThree::~SpecialShapeThree()
{


}

void SpecialShapeThree::computeTriangles()
{

    delete[] m_vertexData;
    int tris = ((m_param1 * m_param2) * 2);
    int triVerts = ((tris * 3) * 6) * 2;
    m_vertexData = new GLfloat[triVerts];


//

    for (int rCount = 0; rCount < m_param2; ++rCount) {
        for (int hCount = 0; hCount < m_param1; ++hCount) {
            float rad = ((PI * 2.0f) * rCount)/m_param2;
            float radP = ((PI * 2.0f) * (rCount + 1))/m_param2;
            float hrad = ((PI * 2.0f) * hCount)/m_param1;
            float hradP = ((PI * 2.0f) * (hCount + 1))/m_param1;


            //Top Right

            glm::vec3 vert1 = glm::vec3(m_radius * cos(rad) * sin(hrad), m_radius * cos(hrad), m_radius * sin(rad) * sin(hrad));
            float x1 = m_radius * cos(rad) * sin(hrad);
            float y1 = m_radius * cos(hrad);
            float z1 = m_radius * sin(rad) * sin(hrad);
            float mag1 = sqrt((x1 * x1) + (y1 * y1) + (z1 * z1));
            glm::vec3 norm1 = glm::vec3(x1/mag1, y1/mag1, z1/mag1);


            //Top left

            glm::vec3 vert2 = glm::vec3(m_radius * cos(radP) * sin(hradP), m_radius * cos(hrad), m_radius * sin(radP) * sin(hradP));
            float x2 = m_radius * cos(radP) * sin(hradP);
            float y2 = m_radius * cos(hrad);
            float z2 = m_radius * sin(radP) * sin(hradP);
            float mag2 = sqrt((x2 * x2) + (y2 * y2) + (z2 * z2));
            glm::vec3 norm2 = glm::vec3(x2/mag2, y2/mag2, z2/mag2);

            //Bottom left

            glm::vec3 vert3 = glm::vec3(m_radius * cos(radP) * sin(hradP), m_radius * cos(hradP), m_radius * sin(radP) * sin(hradP));
            float x3 = m_radius * cos(radP) * sin(hradP);
            float y3 = m_radius * cos(hradP);
            float z3 = m_radius * sin(radP) * sin(hradP);
            float mag3 = sqrt((x3 * x3) + (y3 * y3) + (z3 * z3));
            glm::vec3 norm3 = glm::vec3(x3/mag3, y3/mag3, z3/mag3);


            //Top Right

            glm::vec3 vert4 = glm::vec3(m_radius * cos(rad) * sin(hrad), m_radius * cos(hrad), m_radius * sin(rad) * sin(hrad));
            glm::vec3 norm4 = glm::vec3(x1/mag1, y1/mag1, z1/mag1);


            //Bottom left

            glm::vec3 vert5 = glm::vec3(m_radius * cos(radP) * sin(hradP), m_radius * cos(hradP), m_radius * sin(radP) * sin(hradP));
            glm::vec3 norm5 = glm::vec3(x3/mag3, y3/mag3, z3/mag3);

            //Bottom right

            glm::vec3 vert6 = glm::vec3(m_radius * cos(rad) * sin(hrad), m_radius * cos(hradP), m_radius * sin(rad) * sin(hrad));
            float x4 = m_radius * cos(rad) * sin(hrad);
            float y4 = m_radius * cos(hradP);
            float z4 = m_radius * sin(rad) * sin(hrad);
            float mag4 = sqrt((x4 * x4) + (y4 * y4) + (z4 * z4));
            glm::vec3 norm6 = glm::vec3(x4/mag4, y4/mag4, z4/mag4);


                addVertNorm(vert1, norm1);
                addVertNorm(vert3, norm3);
                addVertNorm(vert2, norm2);
                addVertNorm(vert4, norm4);
                addVertNorm(vert6, norm6);
                addVertNorm(vert5, norm5);
        }
    }
}
