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


GLuint objIndices[] = {
    0, 1, 2, // Bottom side
    0, 2, 3, // Bottom side
    4, 6, 5, // Left side
    7, 9, 8, // Non-facing side
    10, 12, 11, // Right side
    13, 15, 14 // Facing side
};

// Quad vertices with texture coordinates
GLfloat quadVertices[] = {
    // Positions        // TexCoords
    -1.0f,  1.0f,  0.0f,  1.0f, 1.0f,  // Top-left
    -1.0f, -1.0f,  0.0f,  1.0f, 0.0f,  // Bottom-left
     1.0f, -1.0f,  0.0f,  0.0f, 0.0f,  // Bottom-right
     1.0f,  1.0f,  0.0f,  0.0f, 1.0f   // Top-right
};

GLuint quadIndices[] = {
    0, 1, 2,  // First triangle
    0, 2, 3   // Second triangle
};



void setModelUniform(Shader& shader, glm::vec3 Pos, glm::vec3 RotAxis, float rotAngle, glm::vec3 scale);

void closeWindow(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}
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

    Camera camera;

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

    // Create and bind the VAO, VBO, and EBO for the quad
    VertexArray quadVAO;
    VertexBuffer quadVBO(quadVertices, sizeof(quadVertices));
    ElementBuffer quadEBO(quadIndices, sizeof(quadIndices));

    // Define the vertex attributes for the quad
    quadVAO.LinkAttribArray(quadVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);           // Position attribute
    quadVAO.LinkAttribArray(quadVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float))); // TexCoords attribute
    quadVAO.UnbindVertArray();
    quadEBO.UnbindElemBuffer();

    Shader quadShader("quad.vert", "quad.frag");

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

    glm::vec3 lightPos = glm::vec3(0.5f, 2.0f, 0.0f);
    glm::vec3 lightScale = glm::vec3(0.2f);
    glm::vec3 lightRotAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    float lightRotAngle = 0.0f;

    //CREATING FRAMEBUFFER
    unsigned int framebuffer, colorTexture, depthRenderBuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    glGenTextures(1, &colorTexture);
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);

    glGenRenderbuffers(1, &depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "ERROR::FRAMEBUFFER IS NOT COMPLETE::" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    while (!(glfwWindowShouldClose(window)))
    {
        closeWindow(window);
       
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glEnable(GL_DEPTH_TEST);


        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //obj Info
        objShader.UseShader();

        setModelUniform(objShader, objPos, objRotAxis, objRotAngle, objScale);
        camera.setCamVectors(objShader);

        objVAO.BindVertArray();
        glDrawElements(GL_TRIANGLES, sizeof(objIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
        objVAO.UnbindVertArray();


        //light Info
        lightShader.UseShader();

        setModelUniform(lightShader, lightPos, lightRotAxis, lightRotAngle, lightScale);
        camera.setCamVectors(lightShader);

        lightVAO.BindVertArray();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
        lightVAO.UnbindVertArray();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);


        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        quadShader.UseShader();
        glBindTexture(GL_TEXTURE_2D, colorTexture);
        quadVAO.BindVertArray();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();

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