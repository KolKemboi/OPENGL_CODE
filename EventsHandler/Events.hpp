#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <unordered_map>
#include <vector>
#include "Camera.hpp"
#include <iostream>


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
	int width;
	int height;

	WindowResizeEvent(int width, int height) : width(width), height(height)
	{
		this->type = EventType::WindowResized;
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
		if (action == GLFW_PRESS)
		{
			KeyBoardEvent event(EventType::KeyPressed, key, mods);
			eventDispatcher->Dispatch(event);
		}
		else if (action == GLFW_RELEASE)
		{
			KeyBoardEvent event(EventType::KeyReleased, key, mods);
			eventDispatcher->Dispatch(event);
		}
	}

private:
	static EventDispatcher* eventDispatcher;
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


class EventHandler
{
public:
	EventHandler(EventDispatcher& dispatcher, Camera& camera) :
		camera(camera), lastX(400), lastY(400), fistClick(true), deltaTime(0.0f), lastFrame(0.0f)
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

private:
	Camera& camera;
	float lastX, lastY;
	bool fistClick;
	float deltaTime, lastFrame;


	void OnMouseMove(const MouseEvent& event)
	{
		std::cout << "Mouse moved to: (" << event.x << ", " << event.y << ")" << std::endl;
		if (fistClick)
		{
			lastX = event.x;
			lastY = event.y;
			fistClick = false;
		}

		float xOffset = event.x - lastX;
		float yOffset = event.y - lastY;

		lastX = event.x;
		lastY = event.y;

		camera.ProcessMouseMovement(xOffset, yOffset);


	}
	void OnMouseButtonPress(const MouseEvent& event)
	{
		std::cout << "Mouse button pressed at: (" << event.x << ", " << event.y << "), button: " << event.button << std::endl;
	}
	void OnMouseButtonRelease(const MouseEvent& event)
	{
		std::cout << "Mouse button released at: (" << event.x << ", " << event.y << "), button: " << event.button << std::endl;
	}

	void OnKeyPress(const KeyBoardEvent& event)
	{
		std::cout << "Key pressed: " << event.key << " with mods: " << event.mods << std::endl;
		if (event.key == GLFW_KEY_W)
		{
			camera.ProcessKeyboard(FORWARD, deltaTime);
		}
		else if (event.key == GLFW_KEY_S)
		{
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		}
		else if (event.key == GLFW_KEY_A)
		{
			camera.ProcessKeyboard(LEFT, deltaTime);
		}
		else if (event.key == GLFW_KEY_D)
		{
			camera.ProcessKeyboard(RIGHT, deltaTime);
		}
	}

	void OnKeyRelease(const KeyBoardEvent& event)
	{
		std::cout << "Key released: " << event.key << " with mods: " << event.mods << std::endl;
	}

	void OnWindowResize(const WindowResizeEvent& event)
	{
		std::cout << "Window resized to: " << event.width << "x" << event.height << std::endl;
		glViewport(0, 0, event.width, event.height);
	}
};