#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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

	static void MousePositionCallback(GLFWwindow* window, double x, double y)
	{
		xPos = x;
		yPos = y;

		MouseEvent event(EventType::MouseMoved, xPos, yPos);
		eventDispatcher->Dispatch(event);

	}

	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (ImGui::GetIO().WantCaptureMouse)
		{
			ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
		}

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

	static void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		MouseScrollEvent event(yOffset);
		eventDispatcher->Dispatch(event);

		ImGui_ImplGlfw_ScrollCallback(window, xOffset, yOffset);
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
		if (ImGui::GetIO().WantCaptureKeyboard)
		{
			ImGui_ImplGlfw_KeyCallback(window, key, scanCode, action, mods);
		}

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
	EventHandler(EventDispatcher& dispatcher, Camera cam, u_int width, u_int height) :
		m_LastX(width / 2), m_LastY(height / 2), m_Camera(cam)
	{
		dispatcher.Subscribe(EventType::MouseMoved, [this](const Event& event)
			{
				const MouseEvent& mouseMoveEvent = static_cast<const MouseEvent&>(event);
				
				OnMouseMove(mouseMoveEvent);
			});

		dispatcher.Subscribe(EventType::MouseButtonPressed, [this](const Event& event)
			{
				const MouseEvent& mousePressEvent = static_cast<const MouseEvent&>(event);
				
				OnMouseButtonPress(mousePressEvent);
			});
		
		dispatcher.Subscribe(EventType::MouseButtonReleased, [this](const Event& event)
			{
				const MouseEvent& mouseReleaseEvent = static_cast<const MouseEvent&>(event);
				OnMouseButtonRelease(mouseReleaseEvent);
			});
		
		dispatcher.Subscribe(EventType::KeyPressed, [this](const Event& event)
			{
				const KeyboardEvent& keyPressEvent = static_cast<const KeyboardEvent&>(event);
				OnKeyPress(keyPressEvent);
			});
		
		dispatcher.Subscribe(EventType::KeyRelaased, [this](const Event& event)
			{
				const KeyboardEvent& KeyReleaseEvent = static_cast<const KeyboardEvent&>(event);
				OnKeyRelease(KeyReleaseEvent);
			});

		dispatcher.Subscribe(EventType::WindowResized, [this](const Event& event)
			{
				const WindowResizeEvent& windowResize = static_cast<const WindowResizeEvent&>(event);
				OnWindowResize(windowResize);
			});

		dispatcher.Subscribe(EventType::MouseScrolled, [this](const Event& event)
			{
				const MouseScrollEvent& scrollEvent = static_cast<const MouseScrollEvent&>(event);
				OnMouseScrollEvent(scrollEvent);
			});


	}

	void changeLast(u_int width, u_int height)
	{
		m_LastX = static_cast<float>(width / 2);
		m_LastY = static_cast<float>(height / 2);
	}

	float  UpdateDeltaTime()
	{
		float crntFrame = glfwGetTime();
		m_DeltaTime = crntFrame - m_LastFrame;
		m_LastFrame = crntFrame;
		return m_DeltaTime;
	}

	std::unordered_map<std::string, float> GetMousePos() const
	{
		return m_MousePos;
	}

	bool IsLeftMousePressed() const
	{
		return m_IsLeftPressed;
	}

	bool IsRightMousePressed() const
	{
		return m_IsRightPressed;
	}

	bool IsMiddleMousePressed() const
	{
		return m_IsMiddlePressed;
	}

	std::array<bool, 1024> GetKeys() const
	{
		return keyStates;
	}
	std::unordered_map<std::string, int> GetWindowSize() const
	{
		return m_WindowSize;
	}



private:
	Camera& m_Camera;
	float m_LastX, m_LastY;
	bool m_IsLeftPressed = false, m_IsRightPressed = false, m_IsMiddlePressed = false;
	std::array<bool, 1024> keyStates;
	bool m_FirstClick = true;
	float m_LastFrame = 0.0f, m_DeltaTime = 0.0f;
	std::unordered_map<std::string, int> m_WindowSize;
	std::unordered_map < std::string, float> m_MousePos;


private:
	void OnMouseMove(const MouseEvent& event)
	{
		if (m_FirstClick)
		{
			m_LastX = event.x;
			m_LastY = event.y;
			m_FirstClick = false;
		}

		float xOffset = event.x - m_LastX;
		float yOffset = event.y - m_LastY;

		m_LastX = event.x;
		m_LastY = event.y;

		m_MousePos["mouseX"] = event.x;
		m_MousePos["mouseY"] = event.y;


		if (m_IsMiddlePressed)
			m_Camera.LookAround(xOffset, yOffset, m_DeltaTime);

	}
	void OnMouseButtonPress(const MouseEvent& event)
	{
		if (event.button == GLFW_MOUSE_BUTTON_LEFT)
			m_IsLeftPressed = true;
		if (event.button == GLFW_MOUSE_BUTTON_RIGHT)
			m_IsRightPressed = true;
		if (event.button == GLFW_MOUSE_BUTTON_MIDDLE)
			m_IsMiddlePressed = true;
	}

	void OnMouseButtonRelease(const MouseEvent& event)
	{
		if (event.button == GLFW_MOUSE_BUTTON_LEFT)
			m_IsLeftPressed = false;
		if (event.button == GLFW_MOUSE_BUTTON_RIGHT)
			m_IsRightPressed = false;
		if (event.button == GLFW_MOUSE_BUTTON_MIDDLE)
		{
			m_IsMiddlePressed = false; 
			m_FirstClick = false;
		}

	}

	void OnMouseScrollEvent(const MouseScrollEvent& event)
	{
		m_Camera.ZoomAround(event.offset, m_DeltaTime);
	}

	void OnKeyPress(const KeyboardEvent& event)
	{
		keyStates[event.key] = true;
	}

	void OnKeyRelease(const KeyboardEvent& event)
	{
		keyStates[event.key] = false;
	}

	void OnWindowResize(const WindowResizeEvent& event)
	{
		m_WindowSize = event.size;
	}

};
