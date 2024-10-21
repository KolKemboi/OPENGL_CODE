#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>

#include "Model.h"
#include "Shader.h"
#include "Camera.h"


unsigned int width = 800, height = 800;

Camera camera(width, height);
float deltaTime = 0.0f , prevTime = 0.0f;
bool keys[1024];

void DoMovement()
{
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) camera.moveAround(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) camera.moveAround(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) camera.moveAround(LEFT, deltaTime);
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) camera.moveAround(RIGHT, deltaTime);
	if (keys[GLFW_KEY_SPACE] ) camera.moveAround(UP, deltaTime);
	if (keys[GLFW_KEY_LEFT_SHIFT] || keys[GLFW_KEY_RIGHT_SHIFT]) camera.moveAround(DOWN, deltaTime);
}

void KeyCallback(GLFWwindow* window, int key, int sancode, int action, int mode)
{
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)keys[key] = true;
		else if (action == GLFW_RELEASE)keys[key] = false;
	}
}


void closeWindow(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

const char* modelVertFile = "model.vert";
const char* modelFragFile = "model.frag";


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(width, height, "lighting", nullptr, nullptr);
	if (window == NULL)
	{
		std::cerr << "FAILED TO INIT WINDOW" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, static_cast<unsigned int>(width), static_cast<unsigned int>(height));
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");


	Model suzanne("models/suzanne.obj");
	Shader objShader("model.vert", "model.frag");
	Shader liningShader("outlining.vert", "outlining.frag");

	glfwSetKeyCallback(window, KeyCallback);

    while (!(glfwWindowShouldClose(window)))
{
    glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    float crntTime = glfwGetTime();
    deltaTime = crntTime - prevTime;
    prevTime = crntTime;

    DoMovement();
    camera.lookAround(window);
    closeWindow(window);

    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    objShader.UseShader();
    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, glm::vec3(0.0, 0.0, 0.0));  
    modelMat = glm::scale(modelMat, glm::vec3(1.0f));               
    objShader.setMat4("model", modelMat);

    glStencilFunc(GL_ALWAYS, 1, 0xFF);  
    glStencilMask(0xFF);                
    suzanne.Draw(objShader, camera);    
    

    objShader.UseShader();
    glm::mat4 modelMat2 = glm::mat4(1.0f);
    modelMat2 = glm::translate(modelMat2, glm::vec3(1.0, 1.0, 2.0));  
    modelMat2 = glm::scale(modelMat2, glm::vec3(0.5f));               
    objShader.setMat4("model", modelMat2);

    glStencilFunc(GL_ALWAYS, 0, 0xFF);  
    glStencilMask(0x00);                
    suzanne.Draw(objShader, camera);    

    
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);  
    glStencilMask(0x00);                  

    liningShader.UseShader();
    glm::mat4 StenmodelMat = glm::mat4(1.0f);
    StenmodelMat = glm::translate(StenmodelMat, glm::vec3(0.0, 0.0, 0.0));  
    StenmodelMat = glm::scale(StenmodelMat, glm::vec3(1.0f));              
    liningShader.setMat4("model", StenmodelMat);
    liningShader.setFloat("outlineThickness", 0.01);

    suzanne.Draw(liningShader, camera);  

    glStencilFunc(GL_ALWAYS, 1, 0xFF);  
    glStencilMask(0xFF);                
    glEnable(GL_DEPTH_TEST);            

    ImGui::Begin("Debug Window");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwPollEvents();
    glfwSwapBuffers(window);
}



	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();


}
