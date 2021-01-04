#pragma once

float mixValue = 0.5, ss =0.5f;
void processInput(GLFWwindow* window , Camera& cam) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        mixValue += 0.01f;
        if (mixValue >= 1.0f)
            mixValue = 1.0f;

        ss += 0.1f;
        if (ss >= 1.0f)
            ss = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        mixValue -= 0.01f;
        if (mixValue <= 0.0f)
            mixValue = 0.0f;
        ss -= 0.1f;
        if (ss <= 0.0f)
            ss = 0.0f;
    }
    
    cam.UpdateCameraSpeed(DT , 2.5f);
    cam.UpdateFront();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.UpdatePos(1.0f);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.UpdatePos(-1.0f);//cam.UpdatePos(-1)

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        //camPos -= glm::normalize(glm::cross(camFront, camUp)) * cameraSpeed;
        cam.RotateCamera(-50);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        //camPos += glm::normalize(glm::cross(camFront, camUp)) * cameraSpeed;
        cam.RotateCamera(50);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cam.UpdateUp(-1.0f);//cam.UpdateUp
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cam.UpdateUp(1.0f);

}
/*void mouse_input(GLFWwindow* window , double xpos , double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    xoff = xpos - lastX;
    yoff = lastY - ypos;

    xoff *= mouse_sensitivity;
    yoff *= mouse_sensitivity;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    yaw += xoff;
    pitch += yoff;


    glm::vec3 camDir(1.0f);
    camDir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    camDir.y = sin(glm::radians(pitch));
    camDir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    //camFront = glm::normalize(camDir);
}*/
inline void imGui_slider_input() {
    glm::vec3 lamb_vec = lblock.GetAmbientStrength();
    float* lamb = glm::value_ptr(lamb_vec);
    ImGui::SliderFloat3("light.ambient", lamb, 0.0f, 1.0f, "%.3f", 1.0f);
    lblock.SetAmbientStrength(glm::make_vec3(lamb));

    glm::vec3 ldiff_vec = lblock.GetDiffusionFactor();
    float* ldiff = glm::value_ptr(ldiff_vec);
    ImGui::SliderFloat3("light.diffusion", ldiff, 0.0f, 1.0f, "%.3f", 1.0f);
    lblock.SetDiffusionFactor(glm::make_vec3(ldiff));

    glm::vec3 lspec_vec = lblock.GetSpecularStrength();
    float* lspec = glm::value_ptr(lspec_vec);
    ImGui::SliderFloat3("light.specular", lspec, 0.0f, 1.0f, "%.3f", 1.0f);
    lblock.SetSpecularStrength(glm::make_vec3(lspec));
    
}