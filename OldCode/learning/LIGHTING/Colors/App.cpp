#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "Camera.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"

const unsigned int width = 800, height = 800;

GLfloat lightVertices[] = {
    // Front face
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  // Vertex 0
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  // Vertex 1
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  // Vertex 2
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  // Vertex 3

    // Back face
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Vertex 4
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Vertex 5
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Vertex 6
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Vertex 7
};

GLuint lightIndices[] = {
    // Front face
    0, 1, 2,
    2, 3, 0,

    // Back face
    4, 5, 6,
    6, 7, 4,

    // Left face
    0, 3, 7,
    7, 4, 0,

    // Right face
    1, 5, 6,
    6, 2, 1,

    // Top face
    3, 2, 6,
    6, 7, 3,

    // Bottom face
    0, 1, 5,
    5, 4, 0,
};


GLfloat objVerts[] =
{ //     COORDINATES     /        COLORS        /       NORMALS       //
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,     0.0f, -1.0f, 0.0f, // Bottom side
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,     0.0f, -1.0f, 0.0f, // Bottom side
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,     0.0f, -1.0f, 0.0f, // Bottom side
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,     0.0f, -1.0f, 0.0f, // Bottom side

    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,    -0.8f, 0.5f,  0.0f, // Left Side
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,    -0.8f, 0.5f,  0.0f, // Left Side
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,    -0.8f, 0.5f,  0.0f, // Left Side

    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,     0.0f, 0.5f, -0.8f, // Non-facing side
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,     0.0f, 0.5f, -0.8f, // Non-facing side
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,     0.0f, 0.5f, -0.8f, // Non-facing side

     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,     0.8f, 0.5f,  0.0f, // Right side
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,     0.8f, 0.5f,  0.0f, // Right side
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,     0.8f, 0.5f,  0.0f, // Right side

     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,     0.0f, 0.5f,  0.8f, // Facing side
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,      0.0f, 0.5f,  0.8f, // Facing side
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,     0.0f, 0.5f,  0.8f  // Facing side
};


GLuint objIndices[] ={
    0, 1, 2, // Bottom side
    0, 2, 3, // Bottom side
    4, 6, 5, // Left side
    7, 9, 8, // Non-facing side
    10, 12, 11, // Right side
    13, 15, 14 // Facing side
};


int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Colors", nullptr, nullptr);
    if (window == NULL)
    {
        std::cerr << "Failed" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, 800, 800);
    glEnable(GL_DEPTH_TEST);


    VertexArray objVAO;
    VertexBuffer objVBO;
    ElementBuffer objEBO;

    objVBO.BindVertexBuffer();
    objEBO.BindElementBuffer();

    objVBO.LinkData(objVerts, sizeof(objVerts));
    objEBO.LinkData(objIndices, sizeof(objIndices));

    objVAO.LinkAttribArray(objVBO, 0, 3, GL_FLOAT, 9 * sizeof(float), (void*)0);
    objVAO.LinkAttribArray(objVBO, 1, 3, GL_FLOAT, 9 * sizeof(float), (void*)(3*sizeof(float)));
    objVAO.LinkAttribArray(objVBO, 2, 3, GL_FLOAT, 9 * sizeof(float), (void*)(6 * sizeof(float)));

    objVAO.UnbindVertexArray();
    objEBO.UnbindElementBuffer();


    VertexArray lightVAO;
    VertexBuffer lightVBO;
    ElementBuffer lightEBO;

    lightVBO.BindVertexBuffer();
    lightEBO.BindElementBuffer();

    lightVBO.LinkData(lightVertices, sizeof(lightVertices));
    lightEBO.LinkData(lightIndices, sizeof(lightIndices));

    lightVAO.LinkAttribArray(lightVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    lightVAO.LinkAttribArray(lightVBO, 2, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float)));

    lightVAO.UnbindVertexArray();
    lightEBO.UnbindElementBuffer();

    Shader boxShader("default.vert", "default.frag");

    Shader lightShader("color.vert", "color.frag");

    Camera camera;
    float color[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glm::vec3 lightPos = glm::vec3(1.0f, 1.0f, 0.5f);


    //ImGui setUp
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    float rot = 0.0f;
    double prevTime = glfwGetTime();

    while (!(glfwWindowShouldClose(window)))
    {
        glm::vec4 lightColor = glm::vec4(color[0], color[1], color[2], color[3]);

        glfwPollEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //camera.LookAround(window);


        //Imgui Frame Setup
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
     
        //Rotation
        double crntTime = glfwGetTime();
        if (crntTime - prevTime >= 1 / 60)
        {
            rot += 0.05f;
            prevTime = crntTime;
        }

        //light model rendering
        lightShader.UseShader();

        glm::mat4 lightModel = glm::mat4(1.0f);

        lightModel = glm::translate(lightModel, lightPos);
        lightModel = glm::scale(lightModel, glm::vec3(0.2f));
        GLint lightmodelLoc = glGetUniformLocation(lightShader.ShaderProgram, "model");
        glUniformMatrix4fv(lightmodelLoc, 1, GL_FALSE, glm::value_ptr(lightModel));


        //glUniformMatrix4fv(lightmodelLoc, 1, GL_FALSE, glm::value_ptr(lightModel));

        glUniform4f(glGetUniformLocation(lightShader.ShaderProgram, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        camera.setCamera(lightShader);


        lightVAO.BindVertexArray();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
        lightVAO.UnbindVertexArray();

          
         boxShader.UseShader();

         //setting values for the uniforms
         glUniform4f(glGetUniformLocation(boxShader.ShaderProgram, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
         glUniform3f(glGetUniformLocation(boxShader.ShaderProgram, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
         glUniform3f(glGetUniformLocation(boxShader.ShaderProgram, "camPos"), camera.pos.x, camera.pos.y, camera.pos.z);


         //model transforms
         glm::mat4 objmodel = glm::mat4(1.0f);
         objmodel = glm::rotate(objmodel, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
         GLint modelLoc = glGetUniformLocation(boxShader.ShaderProgram, "model");
         glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(objmodel));

         //camera funcs
         camera.setCamera(boxShader);




        objVAO.BindVertexArray();
        glDrawElements(GL_TRIANGLES, sizeof(objIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
        objVAO.UnbindVertexArray();

        //Creating the color picker
        ImGui::Begin("color Picker");
        ImGui::ColorEdit4("Color", color);
        ImGui::End();

        //Imgui rendering block
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}
