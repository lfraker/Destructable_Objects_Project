#include "SpecialShapeOne.h"
#include <cmath>

#define PI 3.14159265



SpecialShapeOne::SpecialShapeOne(int p1, int p2)
    : Shape(p1, p2)
{
    computeTriangles();
}

SpecialShapeOne::~SpecialShapeOne()
{


}

void SpecialShapeOne::computeTriangles()
{
    delete[] m_vertexData;
    int tris = ((m_param1 * m_param2) * 2);
    int triVerts = ((tris * 3) * 6) * 5;
    m_vertexData = new GLfloat[triVerts];


//
    //Cap Top
    float radiInc = (m_radius/m_param1);



    for (int rCount = 0; rCount < m_param2; ++rCount) {
        for (int h = 0; h < m_param1; ++h) {
            float radiDecr = m_radius - (radiInc * h);
            float rad = ((PI * 2.0f) * rCount)/m_param2;
            float radP = ((PI * 2.0f) * (rCount + 1))/m_param2;
            float height = 1.0f - ((1.0/m_param1) * h);

            //Top Right

            glm::vec3 vert1 = glm::vec3(radiDecr * cos(rad), (-m_radius - height), radiDecr * sin(rad));
            glm::vec3 norm1 = glm::vec3(-cos(rad), 0.0f, -sin(rad));


            //Top left

            glm::vec3 vert2 = glm::vec3(radiDecr * cos(radP), (-m_radius - height), radiDecr * sin(radP));
            glm::vec3 norm2 = glm::vec3(-cos(radP), 0.0f, -sin(radP));

            //Bottom left

            glm::vec3 vert3 = glm::vec3((radiDecr - radiInc) * cos(radP), height, (radiDecr - radiInc) * sin(radP));
            glm::vec3 norm3 = glm::vec3(-cos(radP), 0.0f , -sin(radP));


            //Top Right

            glm::vec3 vert4 = glm::vec3(radiDecr * cos(rad), (-m_radius - height), radiDecr * sin(rad));
            glm::vec3 norm4 = glm::vec3(-cos(rad), 0.0f, -sin(rad));


            //bottom left

            glm::vec3 vert5 = glm::vec3((radiDecr - radiInc) * cos(radP), height, (radiDecr - radiInc) * sin(radP));
            glm::vec3 norm5 = glm::vec3(-cos(radP), 0.0f, -sin(radP));

            //Bottom right

            glm::vec3 vert6 = glm::vec3((radiDecr - radiInc) * cos(rad), height, (radiDecr - radiInc) * sin(rad));
            glm::vec3 norm6 = glm::vec3(-cos(rad), 0.0f, -sin(rad));

                addVertNorm(vert1, norm1);
                addVertNorm(vert2, norm2);
                addVertNorm(vert3, norm3);
                addVertNorm(vert4, norm4);
                addVertNorm(vert5, norm5);
                addVertNorm(vert6, norm6);

        }
    }

}

