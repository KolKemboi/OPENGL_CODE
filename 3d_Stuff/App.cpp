#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>

#include "MeshLoader.h"
#include "RenderSystem.h"
#include "Camera.h"
#include "EventsHandler.h"


typedef unsigned int u_int;


u_int width = 1920, height = 1080;
float verts[] =
{
	// POSITION           // COLORS
	// Front face (Z = 0.5)
	0.5,  0.5,  0.5,    1.0, 0.0, 0.0, // Top-right (red)
	0.5, -0.5,  0.5,    0.0, 1.0, 0.0, // Bottom-right (green)
   -0.5, -0.5,  0.5,    0.0, 0.0, 1.0, // Bottom-left (blue)
   -0.5,  0.5,  0.5,    1.0, 1.0, 0.0, // Top-left (yellow)

   // Back face (Z = -0.5)
   0.5,  0.5, -0.5,    1.0, 0.0, 1.0, // Top-right (magenta)
   0.5, -0.5, -0.5,    0.0, 1.0, 1.0, // Bottom-right (cyan)
  -0.5, -0.5, -0.5,    1.0, 1.0, 1.0, // Bottom-left (white)
  -0.5,  0.5, -0.5,    0.5, 0.5, 0.5, // Top-left (gray)

  // Left face (X = -0.5)
 -0.5,  0.5,  0.5,    1.0, 0.0, 0.0, // Top-front (red)
 -0.5, -0.5,  0.5,    0.0, 1.0, 0.0, // Bottom-front (green)
 -0.5, -0.5, -0.5,    0.0, 0.0, 1.0, // Bottom-back (blue)
 -0.5,  0.5, -0.5,    1.0, 1.0, 0.0, // Top-back (yellow)

 // Right face (X = 0.5)
 0.5,  0.5,  0.5,    1.0, 0.0, 1.0, // Top-front (magenta)
 0.5, -0.5,  0.5,    0.0, 1.0, 1.0, // Bottom-front (cyan)
 0.5, -0.5, -0.5,    1.0, 1.0, 1.0, // Bottom-back (white)
 0.5,  0.5, -0.5,    0.5, 0.5, 0.5, // Top-back (gray)

 // Top face (Y = 0.5)
 0.5,  0.5,  0.5,    1.0, 0.5, 0.0, // Front-right (orange)
-0.5,  0.5,  0.5,    0.5, 0.0, 1.0, // Front-left (purple)
-0.5,  0.5, -0.5,    1.0, 1.0, 0.0, // Back-left (yellow)
 0.5,  0.5, -0.5,    0.0, 0.5, 0.5, // Back-right (teal)

 // Bottom face (Y = -0.5)
 0.5, -0.5,  0.5,    0.0, 0.5, 1.0, // Front-right (light blue)
-0.5, -0.5,  0.5,    0.5, 0.0, 0.5, // Front-left (violet)
-0.5, -0.5, -0.5,    1.0, 0.5, 1.0, // Back-left (pink)
 0.5, -0.5, -0.5,    0.5, 1.0, 0.0, // Back-right (lime green)
};

u_int idxs[] =
{
	// Front face
	0, 1, 2,
	2, 3, 0,

	// Back face
	4, 5, 6,
	6, 7, 4,

	// Left face
	8, 9, 10,
	10, 11, 8,

	// Right face
	12, 13, 14,
	14, 15, 12,

	// Top face
	16, 17, 18,
	18, 19, 16,

	// Bottom face
	20, 21, 22,
	22, 23, 20,
};



RenderSystem renderer;
Camera camera;
EventDispatcher dispatcher;
EventHandler eventHandler(dispatcher, camera, width, height);


std::unordered_map<std::string, Mesh> meshes;


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "3d Viewport", nullptr, nullptr);
	if (window == NULL)
	{
		std::cout << "ERROR IN WINDOW CREATION" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	Mouse::SetEventDispatcher(&dispatcher);
	Keyboard::SetEventDispatcher(&dispatcher);
	Window::SetEventDispatcher(&dispatcher);


	glfwSetCursorPosCallback(window, Mouse::MousePositionCallback);
	glfwSetMouseButtonCallback(window, Mouse::MouseButtonCallback);
	glfwSetScrollCallback(window, Mouse::MouseScrollCallback);
	glfwSetKeyCallback(window, Keyboard::KeyboardCallback);
	glfwSetFramebufferSizeCallback(window, Window::FrameBufferSizeCallback);


	Mesh myMesh = mesh_creator(verts, sizeof(verts), idxs, 
		static_cast<u_int>(sizeof(idxs) / sizeof(u_int))
			, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(45.0f, 0.0f, 0.0f));

	Mesh myMesh2 = mesh_creator(verts, sizeof(verts), idxs,
		static_cast<u_int>(sizeof(idxs) / sizeof(u_int))
		, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(45.0f, 0.0f, 0.0f));

	meshes["mesh_1"] = myMesh;
	meshes["mesh_2"] = myMesh2;

	float sensitivity = 20.0f, speed = 10.0f, deltaTime = 0.0f;

	while (!(glfwWindowShouldClose(window)))
	{

		deltaTime = eventHandler.UpdateDeltaTime();

		if (eventHandler.IsLeftMousePressed())
			std::unordered_map<std::string, float> MouseLeftClickPos = eventHandler.GetMousePos();

		if (eventHandler.IsRightMousePressed())
			std::unordered_map<std::string, float> MouseRightClickPos = eventHandler.GetMousePos();

		if (eventHandler.IsMiddleMousePressed())
			std::unordered_map<std::string, float> MouseMiddleClickPos = eventHandler.GetMousePos();

		std::unordered_map<std::string, float> MouseCursorPos = eventHandler.GetMousePos();
		std::unordered_map<std::string, int> windowSize = eventHandler.GetWindowSize();

		
		eventHandler.changeLast(windowSize["width"], windowSize["height"]);

		std::cout << MouseCursorPos["mouseX"] << "\n" << MouseCursorPos["mouseY"] << std::endl;

		std::array<bool, 1024> keys = eventHandler.GetKeys();

		if (keys[GLFW_KEY_ESCAPE])
			glfwSetWindowShouldClose(window, true);

		renderer.initScene();

		for (auto& [key, mesh] : meshes)
		{
			renderer.Render(mesh, camera, width, height);
		}


		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Debug Window");
		ImGui::Text("This Is A Debug Window");

		// Scale controls for mesh_1 and mesh_2
		ImGui::SliderFloat3("Model_1 Scale", &meshes["mesh_1"].m_Transform.m_Scale[0], 0.1f, 5.0f);
		ImGui::SliderFloat3("Model_2 Scale", &meshes["mesh_2"].m_Transform.m_Scale[0], 0.1f, 5.0f);

		// Location controls for mesh_1 and mesh_2
		ImGui::SliderFloat3("Model_1 Location", &meshes["mesh_1"].m_Transform.m_Position[0], -5.0f, 5.0f);
		ImGui::SliderFloat3("Model_2 Location", &meshes["mesh_2"].m_Transform.m_Position[0], -5.0f, 5.0f);

		ImGui::End();


		float temp_sens = sensitivity;
		float temp_speed = speed;
		ImGui::Begin("Change Some defaults");
		ImGui::SliderFloat("Camera Sensitivity", &sensitivity, 0.0f, 100.0f);
		ImGui::SliderFloat("Camera Speed", &speed, 0.0f, 50.0f);
		
		if (temp_sens == sensitivity) camera.SensitivitySetter(sensitivity);
		if (temp_speed == speed) camera.SpeedSetter(speed);
		
		ImGui::End();


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		renderer.clearScene(window);

	}

	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();


}
