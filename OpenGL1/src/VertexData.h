#pragma once
#include"blockMaterials.h"
// <----Coordinates--->  <--NormalVecs--> <--texCoords-->
float vertices[] = {
    // Front face
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f , 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f , 0.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f , 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f , 1.0f,
    // Back face
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,-1.0f, 0.0f , 0.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f,-1.0f, 0.0f , 1.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 0.0f,-1.0f, 1.0f , 1.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 0.0f,-1.0f, 1.0f , 0.0f,
     // Top face
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f , 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f , 1.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f , 1.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f , 0.0f,
      // Bottom face
    -0.5f, -0.5f, -0.5f, 0.0f,-1.0f, 0.0f, 0.0f , 0.0f,
     0.5f, -0.5f, -0.5f, 0.0f,-1.0f, 0.0f, 0.0f , 1.0f,
     0.5f, -0.5f,  0.5f, 0.0f,-1.0f, 0.0f, 1.0f , 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f,-1.0f, 0.0f, 1.0f , 0.0f,
      // Right face
     0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f , 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f , 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f , 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f , 1.0f,
       // Left face             
    -0.5f, -0.5f, -0.5f,-1.0f, 0.0f, 0.0f, 0.0f , 0.0f,
    -0.5f, -0.5f,  0.5f,-1.0f, 0.0f, 0.0f, 0.0f , 1.0f,
    -0.5f,  0.5f,  0.5f,-1.0f, 0.0f, 0.0f, 1.0f , 1.0f,
    -0.5f,  0.5f, -0.5f,-1.0f, 0.0f, 0.0f, 1.0f , 0.0f
};
glm::vec3 cubePositions[] = {
    glm::vec3(1.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -5.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(0.3f, -3.0f, -2.5f),
    glm::vec3(-0.5f,  6.0f, -2.5f),
    glm::vec3(-8.5f,  0.2f, -1.5f),
    glm::vec3(-3.3f,  0.0f, -2.5f)
};
unsigned int index[] = {
    0,  1,   2,  0,  2,  3,    // front
    4,  5,   6,  4,  6,  7,    // back
    8,  9,  10,  8,  10, 11,   // top
    12, 13, 14,  12, 14, 15,   // bottom
    16, 17, 18,  16, 18, 19,   // right
    20, 21, 22,  20, 22, 23   // left
};
glm::vec3 pointLightPositions[] = {
    glm::vec3(0.7f,  0.2f,  2.0f),
    glm::vec3(0.2f, -5.3f, -5.0f),
    glm::vec3(-4.0f, 3.3f, -1.0f),
    glm::vec3(6.0f,  0.2f, 2.0f)
};

int blockSelector = 0;
std::vector <MaterialBlock> database(25);
SpotLightBlock lblock;
FarLightBlock fblock;
PointLightBlock pblock[4];