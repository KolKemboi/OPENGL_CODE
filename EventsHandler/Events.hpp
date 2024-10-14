#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <unordered_map>
#include <vector>
#include "Camera.hpp"
#include <iostream>
#include <array>


enum class EventType
{
	MouseMoved,
	MouseButtonPressed,
	MouseButtonReleased,
	KeyPressed,
	KeyReleased,
	WindowResized,
};

struct Event
{
	EventType type;
};


struct MouseEvent : public Event
{
	double x;
	double y;
	int button;

	MouseEvent(EventType type, double x, double y, int button = -1)
		: x(x), y(y), button(button)
	{
		this->type = type;
	}
};


struct KeyBoardEvent : public Event
{
	int key;
	int mods;

	KeyBoardEvent(EventType type, int key, int mods) : key(key), mods(mods)
	{
		this->type = type;
	}
};

struct WindowResizeEvent : public Event
{
	std::unordered_map<std::string, int> size; // Store width and height as a map

	WindowResizeEvent(int width, int height)
	{
		this->type = EventType::WindowResized;
		size["width"] = width;
		size["height"] = height;
	}
};

class EventDispatcher
{
public:
	using EventCallback = std::function<void(const Event&)>;


	void Subscribe(EventType type, EventCallback callback)
	{
		listeners[type].push_back(callback);
	}

	void Dispatch(const Event& event)
	{
		auto it = listeners.find(event.type);
		if (it != listeners.end())
		{
			for (const auto& callback : it->second)
			{
				callback(event);
			}
		}
	}

private:
	std::unordered_map<EventType, std::vector<EventCallback>> listeners;
};

class Mouse
{
public:
	static double xpos, ypos;
	static bool buttons[3];

	static void SetEventDispatcher(EventDispatcher* dispatcher)
	{
		eventDispatcher = dispatcher;
	}
	static void MousePositionCallback(GLFWwindow* window, double x, double y)
	{
		xpos = x;
		ypos = y;

		MouseEvent event(EventType::MouseMoved, xpos, ypos);
		eventDispatcher->Dispatch(event);
	}

	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (button >= 0 && button < 3)
		{
			if (action == GLFW_PRESS)
			{
				buttons[button] = true;
				MouseEvent event(EventType::MouseButtonPressed, xpos, ypos, button);
				eventDispatcher->Dispatch(event);
			}
			if (action == GLFW_RELEASE)
			{
				buttons[button] = false;
				MouseEvent event(EventType::MouseButtonReleased, xpos, ypos, button);
				eventDispatcher->Dispatch(event);
			}
		}
	}




private:
	static EventDispatcher* eventDispatcher;
};

class Keyboard
{
public:
	static void SetEventDispatcher(EventDispatcher* dispatcher)
	{
		eventDispatcher = dispatcher;
	}

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if(key >= 0 && key < keyStates.size())
		{
			if (action == GLFW_PRESS)
			{
				keyStates[key] = true;
				KeyBoardEvent event(EventType::KeyPressed, key, mods);
				eventDispatcher->Dispatch(event);
			}
			else if (action == GLFW_RELEASE)
			{
				keyStates[key] = false;
				KeyBoardEvent event(EventType::KeyReleased, key, mods);
				eventDispatcher->Dispatch(event);
			}
		}
	}

	static bool IsKeyPressed(int key)
	{
		if (key >= 0 && key < keyStates.size())
		{
			return keyStates[key];
		}
		return false; // Return false for out-of-bounds keys
	}

private:
	static EventDispatcher* eventDispatcher;
	static std::array<bool, 1024> keyStates;
};


class Window
{
public:
	static void SetEventDispatcher(EventDispatcher* dispatcher)
	{
		eventDispatcher = dispatcher;
	}

	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);

		WindowResizeEvent event(width, height);
		eventDispatcher->Dispatch(event);
	}

private:
	static EventDispatcher* eventDispatcher;
};


double Mouse::xpos = 0;
double Mouse::ypos = 0;
bool Mouse::buttons[3] = { false, false, false };
EventDispatcher* Mouse::eventDispatcher = nullptr;
EventDispatcher* Keyboard::eventDispatcher = nullptr;
EventDispatcher* Window::eventDispatcher = nullptr;
std::array<bool, 1024> Keyboard::keyStates = { false };


class EventHandler
{
public:
	EventHandler(EventDispatcher& dispatcher, Camera& camera) :
		camera(camera), lastX(400), lastY(400), firstClick(true), deltaTime(0.0f), lastFrame(0.0f)
	{
		dispatcher.Subscribe(EventType::MouseMoved, [this](const Event& event) {
			const MouseEvent& mouseEvent = static_cast<const MouseEvent&>(event);
			OnMouseMove(mouseEvent);
		});

		dispatcher.Subscribe(EventType::MouseButtonPressed, [this](const Event& event)
			{
				const MouseEvent& mouseEvent = static_cast<const MouseEvent&>(event);
				OnMouseButtonPress(mouseEvent);
			});

		dispatcher.Subscribe(EventType::MouseButtonReleased, [this](const Event& event)
			{
				const MouseEvent& mouseEvent = static_cast<const MouseEvent&>(event);
				OnMouseButtonRelease(mouseEvent);
			});
		
		dispatcher.Subscribe(EventType::KeyPressed, [this](const Event& event)
			{
				const KeyBoardEvent& keyEvent = static_cast<const KeyBoardEvent&>(event);
				OnKeyPress(keyEvent);
			});
		
		dispatcher.Subscribe(EventType::KeyReleased, [this](const Event& event)
			{
				const KeyBoardEvent& keyEvent = static_cast<const KeyBoardEvent&>(event);
				OnKeyRelease(keyEvent);
			});
		
		dispatcher.Subscribe(EventType::WindowResized, [this](const Event& event)
			{
				const WindowResizeEvent& windowEvent= static_cast<const WindowResizeEvent&>(event);
				OnWindowResize(windowEvent);
			});

	}

	void UpdateDeltaTime()
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}

	std::unordered_map<std::string, float> GetMousePos() const
	{
		std::unordered_map<std::string, float> mousePos = {
		{"mouseX", lastX},
		{"mouseY", lastY}
		};
		return mousePos;
	}

	bool IsLeftMousePressed() const
	{
		return leftMousePressed;
	}

	bool IsRightMousePressed() const
	{
		return rightMousePressed;
	}

	bool IsMiddleMousePressed() const
	{
		return middleMousePressed;
	}
	
	std::unordered_map<std::string, int> GetWindowSize() const
	{
		return windowSize;
	}

private:
	Camera& camera;
	float lastX, lastY;
	bool firstClick;
	float deltaTime, lastFrame;
	bool middleMousePressed = false;
	bool leftMousePressed = false;
	bool rightMousePressed = false;
	std::unordered_map<std::string, int> windowSize;

	void OnMouseMove(const MouseEvent& event)
	{
		

		if (firstClick)
		{
			lastX = event.x;
			lastY = event.y;
			firstClick = false;
		}

		float xOffset = event.x - lastX;
		float yOffset = event.y - lastY;

		lastX = event.x;
		lastY = event.y;

		if (middleMousePressed)
			camera.ProcessMouseMovement(xOffset, yOffset);


	}
	void OnMouseButtonPress(const MouseEvent& event)
	{
		if (event.button == GLFW_MOUSE_BUTTON_LEFT)
			leftMousePressed = true;
		
		if (event.button == GLFW_MOUSE_BUTTON_RIGHT)
			rightMousePressed = true;
		
		if (event.button == GLFW_MOUSE_BUTTON_MIDDLE)
			middleMousePressed = true;
	}
	void OnMouseButtonRelease(const MouseEvent& event)
	{
		if (event.button == GLFW_MOUSE_BUTTON_LEFT)
		{
			leftMousePressed = false;
		}
		else if (event.button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			rightMousePressed = false;
		}
		else if (event.button == GLFW_MOUSE_BUTTON_MIDDLE)
		{
			middleMousePressed = false;
			firstClick = true;  // Reset first click flag
		}

	}

	void OnKeyPress(const KeyBoardEvent& event)
	{
		if (Keyboard::IsKeyPressed(GLFW_KEY_W) || Keyboard::IsKeyPressed(GLFW_KEY_UP))
			camera.ProcessKeyboard(FORWARD, deltaTime);

		if (Keyboard::IsKeyPressed(GLFW_KEY_S) || Keyboard::IsKeyPressed(GLFW_KEY_DOWN))
			camera.ProcessKeyboard(BACKWARD, deltaTime);

		if (Keyboard::IsKeyPressed(GLFW_KEY_A) || Keyboard::IsKeyPressed(GLFW_KEY_LEFT))
			camera.ProcessKeyboard(LEFT, deltaTime);

		if (Keyboard::IsKeyPressed(GLFW_KEY_D) || Keyboard::IsKeyPressed(GLFW_KEY_RIGHT))
			camera.ProcessKeyboard(RIGHT, deltaTime);
	}

	void OnKeyRelease(const KeyBoardEvent& event)
	{
	}

	void OnWindowResize(const WindowResizeEvent& event)
	{
		windowSize = event.size;
		glViewport(0, 0, windowSize["width"], windowSize["height"]);
	}
};