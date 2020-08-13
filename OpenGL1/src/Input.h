#pragma once
float mixValue = 0.5;
void processInput(GLFWwindow* window) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        mixValue += 0.01f;
        if (mixValue >= 1.0f)
            mixValue = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        mixValue -= 0.01f;
        if (mixValue <= 0.0f)
            mixValue = 0.0f;
    }
    float cameraSpeed = 2.5f * dt;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camPos += cameraSpeed * camFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camPos -= cameraSpeed * camFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camPos -= glm::normalize(glm::cross(camFront, camUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camPos += glm::normalize(glm::cross(camFront, camUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camPos -= glm::normalize(glm::cross(camFront, camUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camPos += glm::normalize(glm::cross(camFront, camUp)) * cameraSpeed;

}
void mouse_input(GLFWwindow* window , double xpos , double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    xoff = xpos - lastX;
    yoff = lastY - ypos;

    xoff *= mouse_sensitivity;
    yoff *= mouse_sensitivity;

    /*if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;*/
    yaw += xoff;
    pitch += yoff;


    glm::vec3 camDir(1.0f);
    camDir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    camDir.y = sin(glm::radians(pitch));
    camDir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camFront = glm::normalize(camDir);
}