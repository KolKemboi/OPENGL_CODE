#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "MouseEvents.hpp"

// Window dimensions
unsigned int width = 800, height = 800;

// Mouse event handlers
void OnMouseMoved(const Event& event) {
    const MouseEvent& mouseEvent = static_cast<const MouseEvent&>(event);
    std::cout << "Mouse Moved: " << mouseEvent.x << ", " << mouseEvent.y << std::endl;
}

void OnMouseButtonPressed(const Event& event) {
    const MouseEvent& mouseEvent = static_cast<const MouseEvent&>(event);
    std::cout << "Mouse Button Pressed: " << mouseEvent.button << " at (" << mouseEvent.x << ", " << mouseEvent.y << ")" << std::endl;
}

void OnMouseButtonReleased(const Event& event) {
    const MouseEvent& mouseEvent = static_cast<const MouseEvent&>(event);
    std::cout << "Mouse Button Released: " << mouseEvent.button << " at (" << mouseEvent.x << ", " << mouseEvent.y << ")" << std::endl;
}

// Keyboard event handlers
void OnKeyPressed(const Event& event) {
    const KeyboardEvent& keyEvent = static_cast<const KeyboardEvent&>(event);
    std::cout << "Key Pressed: " << keyEvent.key << " with mods: " << keyEvent.mods << std::endl;
}

void OnKeyReleased(const Event& event) {
    const KeyboardEvent& keyEvent = static_cast<const KeyboardEvent&>(event);
    std::cout << "Key Released: " << keyEvent.key << " with mods: " << keyEvent.mods << std::endl;
}

// Close window if Escape key is pressed
void closeWindow(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(width, height, "Inputs Manager", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, static_cast<unsigned int>(width), static_cast<unsigned int>(height));

    // Set up event dispatcher
    EventDispatcher dispatcher;
    Mouse::SetEventDispatcher(&dispatcher);
    Keyboard::SetEventDispatcher(&dispatcher);

    // Subscribe to mouse events
    dispatcher.Subscribe(EventType::MouseMoved, OnMouseMoved);
    dispatcher.Subscribe(EventType::MouseButtonPressed, OnMouseButtonPressed);
    dispatcher.Subscribe(EventType::MouseButtonReleased, OnMouseButtonReleased);

    // Subscribe to keyboard events
    dispatcher.Subscribe(EventType::KeyPressed, OnKeyPressed);
    dispatcher.Subscribe(EventType::KeyReleased, OnKeyReleased);

    // Set GLFW callbacks
    glfwSetCursorPosCallback(window, Mouse::MousePositionCallback);
    glfwSetMouseButtonCallback(window, Mouse::MouseButtonCallback);
    glfwSetKeyCallback(window, Keyboard::KeyCallback);

    while (!glfwWindowShouldClose(window)) {
        closeWindow(window);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.1f, 0.3f, 1.0f); // Clear color

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // Cleanup and terminate
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
