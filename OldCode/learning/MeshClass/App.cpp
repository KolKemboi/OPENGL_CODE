#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>

#include "Mesh.hpp"

const unsigned int width = 800, height = 800;
Vertex vertices[] =
{
    Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
    Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
    Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
    Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)}
};

GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3
};

Vertex lightVertices[] =
{
    Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
    Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
    Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
    Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
};

Camera camera(width, height);

bool keys[1024];
float lastFrame = 0.0f, deltaTime = 0.0f;

void DoMovement()
{
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) camera.MoveAround(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) camera.MoveAround(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_RIGHT]) camera.MoveAround(RIGHT, deltaTime);
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_LEFT]) camera.MoveAround(LEFT, deltaTime);
    if (keys[GLFW_KEY_SPACE]) camera.MoveAround(UP, deltaTime);
    if (keys[GLFW_KEY_LEFT_SHIFT]) camera.MoveAround(DOWN, deltaTime);
}

void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) keys[key] = true;
        else if (action == GLFW_RELEASE) keys[key] = false;
    }
}

void setModelUniform(Shader& shader, glm::vec3 Pos, glm::vec3 RotAxis, float rotAngle, glm::vec3 scale);

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Mesh Class", nullptr, nullptr);
    if (window == NULL)
    {
        std::cerr << "Failed" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, width, height);  // Updated to use constants
    glEnable(GL_DEPTH_TEST);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");



    Shader objShader("default.vert", "default.frag");

    std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    std::vector<GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));

    Mesh floor(verts, ind);

    glm::vec3 objPos = glm::vec3(1.0f, 0.0f, 1.0f);
    glm::vec3 objScale = glm::vec3(2.0f);
    glm::vec3 objRotAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    float objRotAngle = 3.0f;

    VertexArray lightVAO;
    Shader lightShader("light.vert", "light.frag");

    std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
    std::vector<GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));

    Mesh light(lightVerts, lightInd);

    glm::vec3 lightPos = glm::vec3(0.5f, 2.0f, 0.0f);
    glm::vec3 lightScale = glm::vec3(1.0f);
    glm::vec3 lightRotAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    float lightRotAngle = 0.0f;
    
    glfwSetKeyCallback(window, KeyCallBack);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        float crntTime = glfwGetTime();
        deltaTime = crntTime - lastFrame;
        lastFrame = crntTime;

        DoMovement();
        camera.LookAround(window);

        objShader.UseShader();
        setModelUniform(objShader, objPos, objRotAxis, objRotAngle, objScale);
        floor.Draw(objShader, camera);

        lightShader.UseShader();

        setModelUniform(lightShader, lightPos, lightRotAxis, lightRotAngle, lightScale);
        light.Draw(lightShader, camera);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
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
