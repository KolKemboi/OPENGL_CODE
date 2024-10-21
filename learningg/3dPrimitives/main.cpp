#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "shaderClass.h"

const unsigned int width = 800;
const unsigned int height = 800;

// Define the vertices and indices
GLfloat vertices[] = {
    // Front face
    -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  // Vertex 0
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // Vertex 1
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  // Vertex 2
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  // Vertex 3

    // Back face
    -0.5f, -0.5f, -0.5f,  0.5f, 0.1f, 0.5f,// Vertex 4
     0.5f, -0.5f, -0.5f,  0.5f, 0.1f, 0.5f,// Vertex 5
     0.5f,  0.5f, -0.5f,  0.5f, 0.1f, 0.5f,// Vertex 6
    -0.5f,  0.5f, -0.5f,  0.5f, 0.1f, 0.5f,// Vertex 7
};

GLuint indices[] = {
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

class Engine
{
public:
    Engine();
    ~Engine();
    void CreateWindow();
    void RunEngine();
private:
    GLFWwindow* window;
    std::unique_ptr<VAO> myVAO;
    std::unique_ptr<VBO> myVBO;
    std::unique_ptr<EBO> myEBO;
    std::unique_ptr<shaderClass> shader;
};

Engine::Engine(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    CreateWindow();
    if (window == NULL) {
        std::cerr << "FAILED" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);//makes the window the current context in the state
    gladLoadGL();//loads gl

    glViewport(0, 0, 800, 800);
    this->myVAO = std::make_unique<VAO>();
    this->myVBO = std::make_unique<VBO>(vertices, sizeof(vertices));
    this->myEBO = std::make_unique<EBO>(indices, sizeof(indices));
    this->shader = std::make_unique<shaderClass>();

    myEBO->Bind();
    myVAO->LinkAttrib(*myVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    myVAO->LinkAttrib(*myVBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    myVAO->Unbind();
    myEBO->Unbind();
}

Engine::~Engine(){
    glfwTerminate();
    myEBO->Delete();
    myVBO->Delete();
    myVAO->Delete();
    shader->deleteShaderProgram();
    std::cout << "Deleted Everything" << std::endl;
}

void Engine::CreateWindow() {
    this->window = glfwCreateWindow(width, height, "Window", NULL, NULL);
}

void Engine::RunEngine() {
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.1f, 0.3f, 1.0f);//fills the window with purple
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clears both depth and color buffers

        myVAO->Bind();
        shader->useShaderProgram();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);//swaps the buffers
        glfwPollEvents();//processes all pooled events
    }

}

int main() {
    Engine Prim3D;
    Prim3D.RunEngine();
}