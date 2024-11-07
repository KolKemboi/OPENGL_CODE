#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>


#include "MeshLoader.h"
#include "RenderSystem.h"
#include "Camera.h"

typedef unsigned int u_int;


u_int width = 800, height = 800;
float verts[] =
{
	-0.5,  -0.5,  0.0,    0.0,   1.0,   0.0, //GREEN
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


void closeWindow(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

RenderSystem renderer;
Camera camera;

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

	Mesh myMesh = mesh_creator(verts, sizeof(verts), idxs, 
		static_cast<u_int>(sizeof(idxs) / sizeof(u_int))
			, glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(45.0f, 0.0f, 0.0f));

	while (!(glfwWindowShouldClose(window)))
	{
		closeWindow(window);
		/*
		event callbacks, 
			this allows me to edit the window width and height, 
			then when it renders, 
			it used the new width and height;
		then render to a frame buffer;
		then render to an ImGui window;
		*/
		myMesh.m_Transform.m_Scale = glm::vec3(1.0);//this is how I scale it up and down
	

		renderer.initScene();

		renderer.Render(myMesh, camera, width, height);


		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Debug Window");
		ImGui::Text("This Is A Debug Window");
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
