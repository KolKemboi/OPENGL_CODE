#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <vector>
#include <array>
#include <iostream>
#include <unordered_map>
#include "Camera.h"


enum class EventType
{
	MouseMoved,
	MouseButtonPressed,
	MouseButtonReleased,
	MouseScrolled,
	KeyPressed,
	KeyRelaased,
	WindowResized,
};

struct Event
{
	EventType type;
};

struct MouseEvent : public Event
{
	double x, y;
	int button;

	MouseEvent(EventType type, double x, double y, int button = -1) :
		x(x), y(y), button(button)
	{
		this->type = type;
	}
};

struct MouseScrollEvent : public Event
{
	float offset;

	MouseScrollEvent(float offset) :
		offset(offset)
	{
		this->type = EventType::MouseScrolled;
	}
};


struct KeyboardEvent : public Event
{
	int key, mods;

	KeyboardEvent(EventType type, int key, int mods) :
		key(key), mods(mods)
	{
		this->type = type;
	}
};

struct WindowResizeEvent : public Event
{
	std::unordered_map<std::string, int> size;

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
	using EventCallback = std::function<void(Event&)>;

	void Subscribe(EventType event, EventCallback callback)
	{
		listeners[event].push_back(callback);
	}

	void Dispatch(Event& event)
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
	static double xPos, yPos;
	static bool buttons[3];

	static void SetEventDispatcher(EventDispatcher* dispatcher)
	{
		eventDispatcher = dispatcher;
	}

	static void MousePositionCallback(GLFWwindow* widow, double x, double y)
	{
		xPos = x;
		yPos = y;

		MouseEvent event(EventType::MouseMoved, xPos, yPos);
		eventDispatcher->Dispatch(event);

	}

	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if(button >= 0 && button < 3)
		{
			if (action == GLFW_PRESS)
			{
				buttons[button] = true;
				MouseEvent event(EventType::MouseButtonPressed, xPos, yPos, button);
				eventDispatcher->Dispatch(event);
			}
			if (action == GLFW_RELEASE)
			{
				buttons[button] = false;
				MouseEvent event(EventType::MouseButtonReleased, xPos, yPos, button);
				eventDispatcher->Dispatch(event);
			}
		}
	}

	static void MouseScrollCallback(GLFWwindow* window, float xOffset, float yOffset)
	{
		MouseScrollEvent event(yOffset);
		eventDispatcher->Dispatch(event);
	}

private:
	static EventDispatcher* eventDispatcher;
};

EventDispatcher* Mouse::eventDispatcher = nullptr;
double Mouse::xPos = 0.0;
double Mouse::yPos = 0.0;
bool Mouse::buttons[3] = { false, false, false };

class Keyboard
{
public:
	static std::array<bool, 1024> keyPressed;

	static void SetEventDispatcher(EventDispatcher* dispatcher)
	{
		eventDispatcher = dispatcher;
	}

	static void KeyboardCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		if(key >= 0 && key < 1024)
		{
			if (action == GLFW_PRESS)
			{
				keyPressed[key] = true;
				KeyboardEvent event(EventType::KeyPressed, key, mods);
				eventDispatcher->Dispatch(event);
			}
			if (action == GLFW_RELEASE)
			{
				keyPressed[key] = false;
				KeyboardEvent event(EventType::KeyRelaased, key, mods);
				eventDispatcher->Dispatch(event);
			}
		}
	}

	static bool IsPressed(int key)
	{
		if (key >= 0 && keyPressed.size()) return keyPressed[key];
		return false;
	}

private:
	static EventDispatcher* eventDispatcher;
};
EventDispatcher* Keyboard::eventDispatcher = nullptr;
std::array<bool, 1024> Keyboard::keyPressed = { false };


class Window
{
public:
	static void SetEventDispatcher(EventDispatcher* dispatcher)
	{
		eventDispatcher = dispatcher;
	}

	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		WindowResizeEvent event(width, height);
		eventDispatcher->Dispatch(event);
	}

private:
	static EventDispatcher* eventDispatcher;
};

EventDispatcher* Window::eventDispatcher = nullptr;


class EventHandler
{
public:
	EventHandler(Camera cam);

private:
	Camera& camera;
	float lastX, lastY;

};
