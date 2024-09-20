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

struct Models
{
	const char* Name;
	Model model;
	Shader shader;
	glm::vec3 modelPos;
	glm::vec3 modelScale;

	Models(const char* name,const std::string& modelPath, const char* vertFile, const char* fraFile) :
		model(modelPath), shader(vertFile, fraFile), modelPos(glm::vec3(0.0f, 0.0f, 0.0f)), modelScale(glm::vec3(1.0f, 1.0f, 1.0f))
	{
		Name = name;
	}

};

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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");


	Models Suzane("suzane", "models/suzanne.obj", "model.vert", "model.frag");
	Models Cube("cube" , "models/cube.obj", "model.vert", "model.frag");
	Cube.modelScale = glm::vec3(0.03f);
	Cube.modelPos = glm::vec3(0.0f, 2.0f, -3.0f);

	std::vector<Models> sceneModels;
	sceneModels.push_back(Suzane);
	sceneModels.push_back(Cube);

	glfwSetKeyCallback(window, KeyCallback);

	while (!(glfwWindowShouldClose(window)))
	{
		glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		float crntTime = glfwGetTime();
		deltaTime = crntTime - prevTime;
		prevTime = crntTime;

		DoMovement();
		camera.lookAround(window);
		closeWindow(window);

		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		for (unsigned int i = 0; i < sceneModels.size(); i++)
		{
			sceneModels[i].shader.UseShader();

			glm::mat4 modelMat = glm::mat4(1.0f);
			modelMat = glm::translate(modelMat, sceneModels[i].modelPos);
			modelMat = glm::scale(modelMat, sceneModels[i].modelScale);
			sceneModels[i].shader.setMat4("model", modelMat);
			std::cout << sceneModels[i].Name << std::endl;
			sceneModels[i].model.Draw(sceneModels[i].shader, camera);

		}

		//for (auto& obj : sceneModels)
		//{
		//	obj.shader.UseShader();
		//}


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
