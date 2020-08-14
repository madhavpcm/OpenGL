#pragma once
glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camUp = glm::vec3(0.0f, 0.1f, 0.0f);

float dt = 0.0f;
float lastFrame = 0.0f;

float lastX = 400 , lastY = 300;
float xoff = 0.0f, yoff = 0.0f;

bool firstMouse = true;

float mouse_sensitivity = 0.01f;

float yaw = 0.0f, pitch = -89.0f;


float specularStrength =0.5f;