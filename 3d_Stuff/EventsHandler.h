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

