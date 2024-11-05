#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>


#include "MeshLoader.h"
#include "RenderSystem.h"

typedef unsigned int u_int;


u_int width = 800, height = 800;

float verts[] =
{
	// POSITION             //COLORS    
	 0.5,   0.5,  0.0,    1.0,   1.0,   1.0, //WHITE
	 0.5,  -0.5,  0.0,    1.0,   0.0,   0.0, //RED
	-0.5,  -0.5,  0.0,    0.0,   1.0,   0.0, //GREEN
	-0.5,   0.5,  0.0,    0.0,   0.0,   1.0, //BLUE
};

u_int idxs[] =
{
	0, 1, 2,
	2, 3, 0,
};

void closeWindow(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}
RenderSystem renderer;

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
		renderer.initScene();

		renderer.Render(myMesh);


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
