#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "blockMaterials.h"
#include "ErrorChecker.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
float DT = 0.0f;
float LAST_FRAME = 0.0f;
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>
#include"light_Type.h"
#include "VertexData.h"
#include "camera.h"
#include "Input.h"
#include "blockMaterials.h"

//camera s

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
   // glfwSetCursorPosCallback(window, mouse_input);
    glfwSwapInterval(1);

    if (GLEW_OK != glewInit())
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        std::cout << "\n ERROR" << std::endl;

    }
    std::cout << glGetString(GL_VERSION) << std::endl;
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    Camera cam;
    VertexArray va,la;
    VertexBuffer vb(vertices, 6* 4 * 8 *sizeof(float));
    VertexBufferLayout layout;

    readJsonFileStatic(database);
    MaterialBlock currentBlock;
    
    
    layout.Push<float>(3);//Positions 
    layout.Push<float>(3);//Normal 
    layout.Push<float>(2);
    
    va.Bind();
    la.Bind();
    float theta = 0.0f;
    va.AddBuffer(vb, layout);
    la.AddBuffer(vb, layout);

    IndexBuffer ib(index, 36);
    lblock.SetPosition( glm::vec3(1.5f, 0.4f, 2.3f));
    
    Shader shader("Res/shader/"); 
    Shader lightshader("Res/shader/lightcube/");
    Texture box1("Res/RAW/box1.png"), box1speccol("Res/RAW/box1spec.png"),box1emis("Res/RAW/box1emis.jpg");
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

    for (int i = 0; i < sizeof(pointLightPositions) / sizeof(glm::vec3); i++) {
        pblock[i].SetPosition(pointLightPositions[i]);
    }
    while (!glfwWindowShouldClose(window))
    {
        //Input
        //calc
        GL_CHECK(glClearColor(0.0f, 0.3f, 0.3f, 0.3f));
        GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
        /* Render here */

        currentBlock = database[blockSelector];
        
        float radius = 10.0f;

        double CURRENT_FRAME = glfwGetTime();
        DT = CURRENT_FRAME - LAST_FRAME;
        LAST_FRAME= CURRENT_FRAME;
        processInput(window, cam);

        glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        view = glm::lookAt(cam.GetCameraPosition(), cam.GetCameraPosition() + cam.GetCameraFrontVec(), cam.GetCameraUpVec());

        glm::mat4 proj = glm::mat4(1.0f);
        proj = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        shader.Bind();
        shader.setUniformMat4f("view", view);
        shader.setUniformMat4f("projection", proj);
        shader.setUniformvec3("viewPos", cam.GetCameraPosition());

       // shader.setUniformblock_Material(currentBlock);
        shader.setUniformSpotLightBlock(lblock , "lblock");
        shader.setUniformFarLightBlock(fblock , "fblock");
        //shader.setUniformvec3("tBlock.specular", glm::vec3(0.2f));
        shader.setUniformvec3("lblock.position", cam.GetCameraPosition());
        shader.setUniformvec3("lblock.direction", cam.GetCameraFrontVec());

        shader.setUniform1f("tBlock.shine",7.0f);
        box1.Bind(1);
        box1speccol.Bind(2);
        box1emis.Bind(3);
        shader.setUniform1i("tBlock.diffuse", 1);
        shader.setUniform1i("tBlock.specular", 2);
        shader.setUniform1i("tBlock.emission", 3);
       
        for (int I = 0; I < sizeof(cubePositions)/sizeof(glm::vec3); I++) {
            //Model of other cubes
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[I]);
            model = glm::rotate(model, glm::radians(20.0f * I),glm::normalize( glm::vec3(1.0f,0.3f , 2.1f )));
            model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
            shader.setUniformMat4f("model", model);
            renderer.Draw(va, ib, shader);
        }

        ImGui_ImplGlfwGL3_NewFrame();
       
        //Model of light cub
        lightshader.Bind();
        lightshader.setUniformMat4f("projection", proj);
        lightshader.setUniformMat4f("view", view);
        //for (int I = 0; I < sizeof(pointLightPositions) / sizeof(glm::vec3); I++) {
          //  shader.setUniformPointLightBlock(pblock[I], "pblock[" +std::to_string(I) + "]" );
        //}
        for (int I = 0; I < sizeof(pointLightPositions)/sizeof(glm::vec3); I++) {

            glm::mat4 lmodel = glm::mat4(1.0f);
            lmodel = glm::translate(lmodel, pointLightPositions[I]);
            lmodel = glm::rotate(lmodel, glm::radians(23.9f * I * 3.2f), glm::normalize(glm::vec3(1.0f, 0.3f, 2.2f)));
            lmodel = glm::scale(lmodel, glm::vec3(0.3f));
            lightshader.setUniformMat4f("model", lmodel);   
            lightRenderer.Draw(la, ib, lightshader);
        }
        
        

        //Imgui
        {
            static int counter = 0;
            // Display some text (you can use a format string too)
            ImGui::Text("Block Color");
            
            ImGui::SliderInt(currentBlock.GetBlockName().c_str(), &blockSelector ,0, 24);  
            // Edit 1 float using a slider from 0.0f to 1.0f    
            
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
            imGui_slider_input();
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
        renderer.Clear();
        lightRenderer.Clear();
        box1.UnBind();
        box1speccol.UnBind();
        box1emis.UnBind();
        shader.Unbind();
        lightshader.Unbind();
    }
    
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}