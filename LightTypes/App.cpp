//Kemboi Cheruiyot 
//Basic Template
/*
project dependencies
    glfw
    glad
    glm
    imgui
    iostream
    cerrno
    fstream
    sstream
*/

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "ElementBuffer.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Texture.hpp"

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
{ //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
    -1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
    -1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
     1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
     1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
};


GLuint objIndices[] = 
{
    0, 1, 2,
    0, 2, 3
};

void setModelUniform(Shader& shader, glm::vec3 Pos, glm::vec3 RotAxis, float rotAngle, glm::vec3 scale);

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Change Window Name
    GLFWwindow* window = glfwCreateWindow(width, height, "Light Types", nullptr, nullptr);
    if (window == NULL)
    {
        std::cerr << "Failed" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, 800, 800);
    glEnable(GL_DEPTH_TEST);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    Camera camera;

    //Pyramid Info
    VertexArray objVAO;
    VertexBuffer objVBO(objVerts, sizeof(objVerts));
    ElementBuffer objEBO(objIndices, sizeof(objIndices));

    objEBO.BindElemBuffer();
    objVAO.LinkAttribArray(objVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
    objVAO.LinkAttribArray(objVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    objVAO.LinkAttribArray(objVBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    objVAO.LinkAttribArray(objVBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    objVAO.UnbindVertArray();
    objEBO.UnbindElemBuffer();

    Shader objShader("default.vert", "default.frag");

    glm::vec3 objPos = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 objScale = glm::vec3(2.0f);
    glm::vec3 objRotAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    float objRotAngle = 3.0f;

    Texture planksTex("planks.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    planksTex.TexUni(objShader, "tex0", 0);
    Texture planksSpec("planksSpec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
    planksSpec.TexUni(objShader, "tex1", 1);



    //Light Info
    VertexArray lightVAO;
    VertexBuffer lightVBO(lightVertices, sizeof(lightVertices));
    ElementBuffer lightEBO(lightIndices, sizeof(lightIndices));

    lightEBO.BindElemBuffer();
    lightVAO.LinkAttribArray(lightVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    lightVAO.LinkAttribArray(lightVBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    lightVAO.UnbindVertArray();
    lightEBO.UnbindElemBuffer();
    Shader lightShader("light.vert", "light.frag");

    glm::vec3 lightPos = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 lightScale = glm::vec3(0.2f);
    glm::vec3 lightRotAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    float lightRotAngle = 0.0f;

    while (!(glfwWindowShouldClose(window)))
    {
        glfwPollEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        camera.LookAround(window);


        //obj Info
        objShader.UseShader();
        planksTex.Bind();
        planksSpec.Bind();
        glUniform4fv(glGetUniformLocation(objShader.ShaderProgram, "camPos"), 1, glm::value_ptr(camera.camPos));
        glUniform4fv(glGetUniformLocation(objShader.ShaderProgram, "lightColor"), 1, glm::value_ptr(lightColor));
        glUniform4fv(glGetUniformLocation(objShader.ShaderProgram, "lightPos"), 1, glm::value_ptr(lightPos));

        setModelUniform(objShader, objPos, objRotAxis, objRotAngle, objScale);
        camera.setCamVectors(objShader);

        objVAO.BindVertArray();
        glDrawElements(GL_TRIANGLES, sizeof(objIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
        objVAO.UnbindVertArray();


        //light Info
        lightShader.UseShader();
        glUniform4fv(glGetUniformLocation(lightShader.ShaderProgram, "lightColor"), 1, glm::value_ptr(lightColor));
        setModelUniform(lightShader, lightPos, lightRotAxis, lightRotAngle, lightScale);
        camera.setCamVectors(lightShader);

        lightVAO.BindVertArray();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
        lightVAO.UnbindVertArray();

        ImGui::Begin("Hello Debug Mode");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }


    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void setModelUniform(Shader& shader, glm::vec3 Pos, glm::vec3 RotAxis, float rotAngle, glm::vec3 scale)
{
    glm::mat4 Model = glm::mat4(1.0f);
    Model = glm::rotate(Model, rotAngle, RotAxis);
    Model = glm::translate(Model, Pos);
    Model = glm::scale(Model, scale);
    GLint modelLoc = glGetUniformLocation(shader.ShaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(Model));
}