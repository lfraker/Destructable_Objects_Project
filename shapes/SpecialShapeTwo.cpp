#include "SpecialShapeTwo.h"
#include <cmath>

#define PI 3.14159265



SpecialShapeTwo::SpecialShapeTwo(int p1, int p2)
    : Shape(p1, p2)
{
    computeTriangles();
}

SpecialShapeTwo::~SpecialShapeTwo()
{


}

void SpecialShapeTwo::computeTriangles()
{
    delete[] m_vertexData;
    int tris = ((m_param1 * m_param2) * 2);
    int triVerts = ((tris * 3) * 6) * 4;
    m_vertexData = new GLfloat[triVerts];


//
    //Cap Top
    float radiInc = (m_radius/m_param1);

    for(float sign = -1.0f; sign < 2.0f; sign += 2.0f) {
        for (int rCount = 0; rCount < m_param2; ++rCount) {
            for (int h = 0; h < m_param1; ++h) {
                float radiDe = m_radius - (radiInc * h);
                float radiDeN = m_radius - (radiInc * (h + 1));
                float rad = ((PI * 2.0f) * rCount)/m_param2;
                float radP = ((PI * 2.0f) * (rCount + 1))/m_param2;
                float hVar = (1.0f - (1.0/m_param1)) - ((1.0/m_param1) * h);
                float hVarN = (1.0f - (1.0/m_param1)) - ((1.0/m_param1) * (h + 1));
                float height = hVar + ((hVar - hVarN) * (rad/(PI * 2.0f)));
                float radiDecr = radiDe + ((radiDe - radiDeN) * (rad/(PI * 2.0f)));
                //Top Right

                glm::vec3 vert1 = glm::vec3(radiDecr * cos(rad), height, radiDecr * sin(rad));
                glm::vec3 norm1 = glm::vec3(0.0f, sign * 1.0f, 0.0f);


                //Top left

                glm::vec3 vert2 = glm::vec3(radiDecr * cos(radP), height, radiDecr * sin(radP));
                glm::vec3 norm2 = glm::vec3(0.0f,sign *  1.0f, 0.0f);

                //Bottom left

                glm::vec3 vert3 = glm::vec3((radiDecr - radiInc) * cos(radP), height, (radiDecr - radiInc) * sin(radP));
                glm::vec3 norm3 = glm::vec3(0.0f, sign * 1.0f , 0.0f);


                //Top Right

                glm::vec3 vert4 = glm::vec3(radiDecr * cos(rad), height, radiDecr * sin(rad));
                glm::vec3 norm4 = glm::vec3(0.0f, sign * 1.0f, 0.0f);


                //bottom left

                glm::vec3 vert5 = glm::vec3((radiDecr - radiInc) * cos(radP), height, (radiDecr - radiInc) * sin(radP));
                glm::vec3 norm5 = glm::vec3(0.0f, sign * 1.0f, 0.0f);

                //Bottom right

                glm::vec3 vert6 = glm::vec3((radiDecr - radiInc) * cos(rad), height, (radiDecr - radiInc) * sin(rad));
                glm::vec3 norm6 = glm::vec3(0.0f, sign * 1.0f, 0.0f);

                if (sign < 0.0f) {
                    addVertNorm(vert1, norm1);
                    addVertNorm(vert2, norm2);
                    addVertNorm(vert3, norm3);
                    addVertNorm(vert4, norm4);
                    addVertNorm(vert5, norm5);
                    addVertNorm(vert6, norm6);
                }
                else {
                    addVertNorm(vert1, norm1);
                    addVertNorm(vert3, norm3);
                    addVertNorm(vert2, norm2);
                    addVertNorm(vert4, norm4);
                    addVertNorm(vert6, norm6);
                    addVertNorm(vert5, norm5);
                }
            }
        }
    }

    for(float sign = -1.0f; sign < 2.0f; sign += 2.0f) {
        for (int rCount = 0; rCount < m_param2; ++rCount) {
            for (int h = 0; h < m_param1; ++h) {
                float radiDe = m_radius - (radiInc * h);
                float radiDeN = m_radius - (radiInc * (h + 1));
                float rad = -((PI * 2.0f) * rCount)/m_param2;
                float radP = -((PI * 2.0f) * (rCount - 1))/m_param2;
                float hVar = (-1.0f + (1.0/m_param1)) + ((1.0/m_param1) * h);
                float hVarN = (-1.0f + (1.0/m_param1)) + ((1.0/m_param1) * (h + 1));
                float height = hVar + ((hVar - hVarN) * (-rad/(PI * 2.0f)));
                float radiDecr = radiDe + ((radiDe - radiDeN) * (-rad/(PI * 2.0f)));


                //Top Right

                glm::vec3 vert1 = glm::vec3(radiDecr * cos(rad), height, radiDecr * sin(rad));
                glm::vec3 norm1 = glm::vec3(0.0f, sign * 1.0f, 0.0f);


                //Top left

                glm::vec3 vert2 = glm::vec3(radiDecr * cos(radP), height, radiDecr * sin(radP));
                glm::vec3 norm2 = glm::vec3(0.0f, sign * 1.0f, 0.0f);

                //Bottom left

                glm::vec3 vert3 = glm::vec3((radiDecr - radiInc) * cos(radP), height, (radiDecr - radiInc) * sin(radP));
                glm::vec3 norm3 = glm::vec3(0.0f, sign * 1.0f , 0.0f);


                //Top Right

                glm::vec3 vert4 = glm::vec3(radiDecr * cos(rad), height, radiDecr * sin(rad));
                glm::vec3 norm4 = glm::vec3(0.0f, sign * 1.0f, 0.0f);


                //bottom left

                glm::vec3 vert5 = glm::vec3((radiDecr - radiInc) * cos(radP), height, (radiDecr - radiInc) * sin(radP));
                glm::vec3 norm5 = glm::vec3(0.0f, sign * 1.0f, 0.0f);

                //Bottom right

                glm::vec3 vert6 = glm::vec3((radiDecr - radiInc) * cos(rad), height, (radiDecr - radiInc) * sin(rad));
                glm::vec3 norm6 = glm::vec3(0.0f, sign * 1.0f, 0.0f);

                if (sign < 0.0f) {
                    addVertNorm(vert1, norm1);
                    addVertNorm(vert2, norm2);
                    addVertNorm(vert3, norm3);
                    addVertNorm(vert4, norm4);
                    addVertNorm(vert5, norm5);
                    addVertNorm(vert6, norm6);
                }
                else {
                    addVertNorm(vert1, norm1);
                    addVertNorm(vert3, norm3);
                    addVertNorm(vert2, norm2);
                    addVertNorm(vert4, norm4);
                    addVertNorm(vert6, norm6);
                    addVertNorm(vert5, norm5);
                }
            }
        }
    }

}
