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

    //Light Info
    VertexArray lightVAO;
    VertexBuffer lightVBO(lightVertices, sizeof(lightVertices));
    ElementBuffer lightEBO(lightIndices, sizeof(lightIndices));

    lightEBO.BindElemBuffer();
    lightVAO.LinkAttribArray(lightVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    lightVAO.LinkAttribArray(lightVBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    lightVAO.UnbindVertArray();
    lightEBO.UnbindElemBuffer();


    while (!(glfwWindowShouldClose(window)))
    {
        glfwPollEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        //obj Info
        objShader.UseShader();
        objVAO.BindVertArray();
        glDrawElements(GL_TRIANGLES, sizeof(objIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
        objVAO.UnbindVertArray();


        // Info
        lightVAO.BindVertArray();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
        lightVAO.UnbindVertArray();

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
