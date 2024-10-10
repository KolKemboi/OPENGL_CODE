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

#include "Events/EventHandler.hpp"

float lastFrame = 0.0f, deltaTime = 0.0f;

const unsigned int width = 800, height = 800;
Camera camera;

EventHandler handler(camera);

// GLFW callback functions
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Placeholder for key input logic
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    MouseMovement mouseMoveEvent(xpos, ypos);
    handler.onEvent(mouseMoveEvent);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    MouseScrollEvent scrollEvent(xoffset, yoffset);
    handler.onEvent(scrollEvent);
}

void windowSizeCallback(GLFWwindow* window, int width, int height) {
    WindowResizeEvent resizeEvent(width, height);
    handler.onEvent(resizeEvent);
}


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


GLuint objIndices[] = {
    0, 1, 2, // Bottom side
    0, 2, 3, // Bottom side
    4, 6, 5, // Left side
    7, 9, 8, // Non-facing side
    10, 12, 11, // Right side
    13, 15, 14 // Facing side
};

void setModelUniform(Shader& shader, glm::vec3 Pos, glm::vec3 RotAxis, float rotAngle, glm::vec3 scale);

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Change Window Name
    GLFWwindow* window = glfwCreateWindow(width, height, "Change Window Name", nullptr, nullptr);
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


    //Pyramid Info
    VertexArray objVAO;
    VertexBuffer objVBO(objVerts, sizeof(objVerts));
    ElementBuffer objEBO(objIndices, sizeof(objIndices));

    objEBO.BindElemBuffer();
    objVAO.LinkAttribArray(objVBO, 0, 3, GL_FLOAT, 9 * sizeof(float), (void*)0);
    objVAO.LinkAttribArray(objVBO, 1, 3, GL_FLOAT, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    objVAO.LinkAttribArray(objVBO, 2, 3, GL_FLOAT, 9 * sizeof(float), (void*)(6 * sizeof(float)));
    objVAO.UnbindVertArray();
    objEBO.UnbindElemBuffer();

    Shader objShader("default.vert", "default.frag");

    glm::vec3 objPos = glm::vec3(1.0f, 0.0f, 1.0f);
    glm::vec3 objScale = glm::vec3(2.0f);
    glm::vec3 objRotAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    float objRotAngle = 3.0f;


    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetWindowSizeCallback(window, windowSizeCallback);



    while (!(glfwWindowShouldClose(window)))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Update event handler with delta time
        handler.setDeltaTime(deltaTime);


        glfwPollEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        //obj Info
        objShader.UseShader();

        setModelUniform(objShader, objPos, objRotAxis, objRotAngle, objScale);
        camera.setCamVectors(objShader);

        objVAO.BindVertArray();
        glDrawElements(GL_TRIANGLES, sizeof(objIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
        objVAO.UnbindVertArray();

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