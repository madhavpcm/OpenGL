#include <Gl/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.h"
#include "ErrorChecker.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "git/imgui/imgui.h"
#include "git/imgui/imgui_impl_glfw_gl3.h"

float mixValue = 0.5;
float X = 90.0f;
float Y = 90.0f;
float camX = 0.0f;
float camY = 0.0f;
float camZ = 9.0f;
void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        mixValue += 0.01f; 
        if (mixValue >= 0.0f)
            mixValue = 0.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        mixValue -= 0.01f; 
        if (mixValue <= -1.0f)
            mixValue = -1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camX -= 0.1f;
        if (camX <= -10.0f)
            camX = -10.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camX += 0.1f;
        if (camX >= 10.0f)
            camX = 10.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camZ += 0.1f;
        if (camZ >= 10.0f)
            camZ = 10.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camZ -= 0.1f;
        if (camZ >= 6.0f)
            camZ = 6.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        camY += 0.1f;
        if (camY >= 10.0f)
            camY = 10.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        camY -= 0.1f;
        if (camY >= 0.0f)
            camY = 0.0f;
    }
}

bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (GLEW_OK != glewInit())
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        std::cout << "\n ERROR" << std::endl;

    }
    std::cout << glGetString(GL_VERSION) << std::endl;
 
{
    float vertices[] = {
          -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
          0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

         -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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
    glm::vec3 lightPositions[]{
        glm::vec3(1.2f, 1.0f, 2.0f)
    };
    unsigned int index[] = {
        0,1,2,
        2,3,0,
    };


    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    
    VertexArray va,la;
    VertexBufferLayout layout;
    VertexBuffer vb(vertices,  36 * 5 * sizeof(float));
    vb.Bind();

    layout.Push<float>(3);/*SEtting up the layout, we say each vertex element consists of 2 sets of coordinates (vertex coord and texture coord_)*/
    layout.Push<float>(2);

    va.Bind();
    la.Bind();

    va.AddBuffer(vb, layout);
    la.AddBuffer(vb, layout);

    IndexBuffer ib(index, 12);
    
    Shader shader("Res/shader/"); 
    Shader lightshader("Res/shader/lightcube/");

    float r = 0.0f;
    float i = 0.05f;

    va.UnBind();
    vb.UnBind();
    ib.UnBind();
    //shader.Unbind();
    lightshader.Unbind();

    Renderer renderer;
    Renderer lightRenderer;
    ImGui::CreateContext(); 
    ImGui_ImplGlfwGL3_Init(window, true);
    
    ImGui::StyleColorsDark();

    while (!glfwWindowShouldClose(window))
    {
        //Input
        processInput(window);
        //calc
        mixValue;
        /* Render here */
        renderer.Clear();
        lightRenderer.Clear();

        float radius = 10.0f;
        glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(-camX, -camY, -camZ), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 proj = glm::mat4(1.0f);
        proj = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        shader.Bind();
        shader.setUniform3f("objectColor", 1.0f, 0.5f, 0.31f);
        shader.setUniform3f("lightColor", 1.0f + mixValue, 1.0f +mixValue, 1.0f +mixValue);
        shader.setUniformMat4f("view", view);
        shader.setUniformMat4f("projection", proj);
        for (int I = 0; I < 2; I++) {
            //Model of other cubes
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[I]);
            shader.setUniformMat4f("model", model);
            renderer.Draw(va, ib, shader);
        }

        //tex1.Bind(0);
        //tex2.Bind(1);

        ImGui_ImplGlfwGL3_NewFrame();

        //Model of light cub
        glm::mat4 lmodel = glm::mat4(1.0f);
        lmodel = glm::translate(lmodel, lightPositions[0]);
        lmodel = glm::scale(lmodel, glm::vec3(0.3f));
        lightshader.Bind();
        lightshader.setUniformMat4f("projection", proj);
        lightshader.setUniformMat4f("view", view);
        lightshader.setUniformMat4f("model", lmodel);        
        lightRenderer.Draw(la, ib, lightshader);

        shader.Unbind();
        lightshader.Unbind();
        //Imgui
        {
            static float f = 0.0f;
            static int counter = 0;
            ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
    }
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}