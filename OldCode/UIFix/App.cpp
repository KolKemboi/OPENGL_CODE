#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>



typedef unsigned int u_int;

GLFWwindow* window;

GLuint framebuffer;
GLuint textureColorbuffer;
GLuint rbo;

void initFramebuffer(u_int width, u_int height);
void resizeFramebuffer(u_int newWidth, u_int newHeight);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

u_int width = 1920, height = 1080;

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
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);

	float rand1 = 1.0f, rand2 = 2.0f, rand3 = 3.0f, rand4 = 4.0f, rand5 = 5.0f, rand6 = 6.0f, rand7 = 7.0f, rand8 = 8.0f, rand9 = 9.0f;

	while (!(glfwWindowShouldClose(window)))
	{
        


        // Get the current size of the window and adjust the framebuffer accordingly
        int newWidth, newHeight;
        glfwGetFramebufferSize(window, &newWidth, &newHeight);

        if (newWidth != width || newHeight != height)
        {
            width = newWidth;
            height = newHeight;
            resizeFramebuffer(width, height);  // Adjust framebuffer size
        }

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("DockSpace Window", nullptr, ImGuiWindowFlags_NoTitleBar
            | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus
            | ImGuiWindowFlags_NoNavFocus);

        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0, 0), ImGuiDockNodeFlags_PassthruCentralNode);

        ImGui::End();

        ImGui::Begin("Scene");
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        u_int viewWidth = static_cast<u_int>(viewportSize.x);
        u_int viewHeight = static_cast<u_int>(viewportSize.y);

        ImVec2 mousePos = ImGui::GetMousePos();  // Get the current mouse position
        ImVec2 windowPos = ImGui::GetWindowPos();  // Get the top-left position of the window

        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2, 0.1, 0.3, 1.0); // Clear the framebuffer
        glViewport(0, 0, width, height);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);  // Unbind framebuffer
		glDisable(GL_DEPTH_TEST);

        ImGui::Image((void*)textureColorbuffer, ImVec2(viewWidth, viewHeight));

        ImGui::End();

        // Debug Window
        ImGui::Begin("Debug Window");
        ImGui::Text("This Is A Debug Window");

        ImGui::SliderFloat("Randome1", &rand1, 0.0, 10.0);
        ImGui::SliderFloat("Randome2", &rand2, 0.0, 10.0);
        ImGui::SliderFloat("Randome3", &rand3, 0.0, 10.0);
        ImGui::SliderFloat("Randome4", &rand4, 0.0, 10.0);
        ImGui::SliderFloat("Randome5", &rand5, 0.0, 10.0);
        ImGui::SliderFloat("Randome6", &rand6, 0.0, 10.0);
        ImGui::SliderFloat("Randome7", &rand7, 0.0, 10.0);
        ImGui::SliderFloat("Randome8", &rand8, 0.0, 10.0);
        ImGui::SliderFloat("Randome9", &rand9, 0.0, 10.0);

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();


	}

	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();


}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

    // Debug print for tracking
    const char* actionType = (action == GLFW_PRESS) ? "Pressed" :
        (action == GLFW_RELEASE) ? "Released" : "Unknown";
    std::cout << "Mouse Button: " << button
        << ", Action: " << actionType
        << ", Mods: " << mods << std::endl;
}


// Cursor Position Callback
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(static_cast<float>(xpos), static_cast<float>(ypos));
     
    std::cout << "Cursor Position - X: " << xpos << ", Y: " << ypos << std::endl;
}

// Scroll Callback
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    std::cout << "Scroll - X Offset: " << xoffset << ", Y Offset: " << yoffset << std::endl;
}

// Key Press Callback (Optional for Debugging Keyboard)
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

    // Debug print for tracking
    const char* actionType = (action == GLFW_PRESS) ? "Pressed" :
        (action == GLFW_RELEASE) ? "Released" : "Unknown";
    std::cout << "Mouse Button: " << button
        << ", Action: " << actionType
        << ", Mods: " << mods << std::endl;
}


void initFramebuffer(u_int width, u_int height)
{
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// Create a texture to store the color buffer
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	// Create a renderbuffer object for depth and stencil attachments
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR: Framebuffer not complete!" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);  // Unbind framebuffer
}

void resizeFramebuffer(u_int newWidth, u_int newHeight)
{
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, newWidth, newHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, newWidth, newHeight);

	glViewport(0, 0, newWidth, newHeight);
}