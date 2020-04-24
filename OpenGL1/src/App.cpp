#include <Gl/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <sstream>

#include "Texture.h"
#include "ErrorChecker.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(600, 600, "Triangle", NULL, NULL);
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
    float positions[] = {
        -0.5f,-0.5f, 0.0f ,0.0f,
         0.5f, 0.5f, 1.0f , 1.0f,
         0.5f,-0.5f, 1.0f , 0.0f,
        -0.5f, 0.5f, 0.0f , 1.0f
    };
    unsigned int index[] = {
        0,1,2,
        0,1,3
    };

    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    float movx = 0.0f, movy = 0.0f;
    VertexArray va;
    VertexBufferLayout layout;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    layout.Push<float>(2);
    layout.Push<float>(2);

    va.AddBuffer(vb, layout);

 
    IndexBuffer ib(index, 6);

    Shader shader("Res/shader/traingle.shader");
    shader.Bind();
    //shader.setUniform4f("u_color", 0.5f, 0.3f, 0.7f, 0.7f);

    float r = 0.0f;
    float i = 0.05f;

    Texture tex("Res/RAW/ez.png");
    tex.Bind();
    shader.setUniform1i("u_Texture", 0);

    va.UnBind();
    vb.UnBind();
    ib.UnBind();
    shader.Unbind();

    Renderer renderer;

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        shader.Bind();
       //shader.setUniform4f("u_color", r , 0.3f, 0.7f, 0.7f);
        shader.setUniform1i("u_Texture", 0);
        va.Bind();
        ib.Bind();

        renderer.Draw(va, ib, shader);

        if (r > 1.0f)
            i = -i;
        else if (r < 0.0f)
            i = -i;
        r += i;
        /*
        movx = 0.0f, movy = 0.0f;
        switch (_getch()) {
        case 97:
            movx = -1.0f;
            break;
        case 115:
            movy = -1.0f;
            break;
        case 100:
            movx = 1.0f;
            break;
        case 119:
            movy = 1.0f;
            break;
        }

        for (int z = 0; z < 6; z++)
            if (z % 2 == 0)
                positions[z] += movy;
            else
                positions[z] += movx;

        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);*/
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}
    
    glfwTerminate();
    return 0;
}