#include <iostream>
#include "imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

unsigned int width = 800;
unsigned int height = 800;

GLFWwindow* createWindow(unsigned int width, unsigned int height) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "IMGUI_FUNCS", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to init window" << std::endl;
		glfwTerminate();
	}
	else {
		return window;
	}
}

ImGuiIO& ImGuiSetUp(GLFWwindow* window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	return io;
}

void ImGuiFrames() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

bool Checked = false;
static int selected = 0;

int main() {
	GLFWwindow* window = createWindow(width,height);
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	ImGuiIO& io = ImGuiSetUp(window);


	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		ImGuiFrames();

		ImGui::Begin("Imgui Window");
		ImGui::Text("Helloooooo");
		ImGui::Checkbox("Check Me", &Checked); //check box

		const char* items[] = { "Item 1", "Item 2", "Item 3" };
		static int currentItem = 0;
		ImGui::Combo("Select Item", &currentItem, items, IM_ARRAYSIZE(items));

		ImGui::End();

		
		
		ImGui::Begin("Another Window");
		ImGui::RadioButton("Option 1", 0);
		ImGui::RadioButton("Option 2", 1);
		
		char buffer[128] = "";
		ImGui::InputText("text Input", buffer, IM_ARRAYSIZE(buffer));
		ImGui::Text(buffer);
		if (ImGui::TreeNode("Node")) {
			ImGui::BulletText("This is a Tree Node");
			ImGui::BulletText("This is a Tree Node");
			ImGui::BulletText("This is a Tree Node");
			ImGui::BulletText("This is a Tree Node");
			ImGui::BulletText("This is a Tree Node");
			ImGui::TreePop();
		}
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}