#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include "Camera.hpp"

const unsigned int width = 800;
const unsigned int height = 800;
int SCREEN_WIDTH;
int SCREEN_HEIGHT;

void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mode);
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = width / 2.0f;
GLfloat lastY = width / 2.0f;
bool keys[1024];
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat prevTime = 0.0f;

void WindowHints() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
GLFWwindow* CreateWindow(const unsigned int width, const unsigned int height) {
	GLFWwindow* window = glfwCreateWindow(width, height, "Camera Funcs", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		std::cerr << "Failed" << std::endl;
	}
	return window;
}

GLfloat vertices[] = {
    // Front face
    -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  // Vertex 0
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  // Vertex 1
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // Vertex 2
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  // Vertex 3

    // Back face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,// Vertex 4
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,// Vertex 5
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,// Vertex 6
    -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,// Vertex 7
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



int main() {
	glfwInit();
	WindowHints();

	GLFWwindow* window = CreateWindow(width, height);
    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
	glfwMakeContextCurrent(window);
	gladLoadGL(); 
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetScrollCallback(window, ScrollCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    VAO VAO1;
    VAO1.Bind();
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));
    EBO1.Bind();
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6*(sizeof(float)), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6*(sizeof(float)), (void*)(3*sizeof(float)));
    
    VAO1.Unbind();
    EBO1.Unbind();
    
    shaderClass Shader;

    glEnable(GL_DEPTH_TEST);


    glm::vec3 cubePos[] =
    {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 2.0f, -4.0f),
        glm::vec3(2.0f, -2.0f, -4.0f),
        glm::vec3(0.0f, -2.0f, 3.0f),
        glm::vec3(-1.0f, 2.0f, 2.0f),
        glm::vec3(1.0f, 2.0f, 2.0f),
        glm::vec3(0.0f, -4.0f, 2.0f),
        glm::vec3(0.0f, 0.0f, -4.0f),
    };

	while (!glfwWindowShouldClose(window)) 
    {
        GLfloat crntTime = glfwGetTime();
        deltaTime = crntTime - prevTime;
        prevTime = crntTime;

		glfwPollEvents();
        DoMovement(); 
		glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Shader.UseShader();
        
        glm::mat4 proj = glm::perspective(camera.GetZoom(), (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view;
        view = camera.GetViewMat();

        GLint modelLoc = glGetUniformLocation(Shader.ShaderProg, "model");
        GLint viewLoc = glGetUniformLocation(Shader.ShaderProg, "view");
        GLint projLoc = glGetUniformLocation(Shader.ShaderProg, "proj");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
        VAO1.Bind();


        
        for (GLuint i = 0; i < sizeof(cubePos)/sizeof(glm::vec3); i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePos[i]);
            GLfloat angle = 20.0f * i;
            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        }
		glfwSwapBuffers(window);
	}

    VBO1.Delete();
    EBO1.Delete();
    VAO1.Delete();
    Shader.DeleteShader();
    glfwDestroyWindow(window);
	glfwTerminate();
}


void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key >= 0 && key < 1024)
    {
        if (GLFW_PRESS == action)
        {
            keys[key] = true;
        }
        else if (GLFW_RELEASE == action)
        {
            keys[key] = false;
        }
    }
}

void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    camera.ProcessMouseScroll(yOffset);
}
void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMov(xOffset, yOffset);

}
void DoMovement()
{
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

}