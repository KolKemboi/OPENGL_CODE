#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <unordered_map>
#include <vector>

enum class EventType {
    MouseMoved,
    MouseButtonPressed,
    MouseButtonReleased,
    KeyPressed,
    KeyReleased,
};

// Base event structure
struct Event {
    EventType type;
};

// Mouse event structure
struct MouseEvent : public Event {
    double x;
    double y;
    int button;

    MouseEvent(EventType type, double x, double y, int button)
        : x(x), y(y), button(button) {
        this->type = type;
    }
};

// Keyboard event structure
struct KeyboardEvent : public Event {
    int key;
    int mods;

    KeyboardEvent(EventType type, int key, int mods)
        : key(key), mods(mods) {
        this->type = type;
    }
};

class EventDispatcher {
public:
    using EventCallback = std::function<void(const Event&)>;

    void Subscribe(EventType type, EventCallback callback) {
        listeners[type].push_back(callback);
    }

    void Dispatch(const Event& event) {
        auto it = listeners.find(event.type);
        if (it != listeners.end()) {
            for (const auto& callback : it->second) {
                callback(event);
            }
        }
    }

private:
    std::unordered_map<EventType, std::vector<EventCallback>> listeners;
};

class Mouse {
public:
    static double xpos, ypos;
    static bool buttons[3];

    static void SetEventDispatcher(EventDispatcher* dispatcher) {
        eventDispatcher = dispatcher;
    }

    static void MousePositionCallback(GLFWwindow* window, double x, double y) {
        xpos = x;
        ypos = y;

        MouseEvent event(EventType::MouseMoved, xpos, ypos, -1);
        eventDispatcher->Dispatch(event);
    }

    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        if (button >= 0 && button < 3) {
            if (action == GLFW_PRESS) {
                buttons[button] = true;
                MouseEvent event(EventType::MouseButtonPressed, xpos, ypos, button);
                eventDispatcher->Dispatch(event);
            }
            else if (action == GLFW_RELEASE) {
                buttons[button] = false;
                MouseEvent event(EventType::MouseButtonReleased, xpos, ypos, button);
                eventDispatcher->Dispatch(event);
            }
        }
    }

private:
    static EventDispatcher* eventDispatcher;
};

class Keyboard {
public:
    static void SetEventDispatcher(EventDispatcher* dispatcher) {
        eventDispatcher = dispatcher;
    }

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS) {
            KeyboardEvent event(EventType::KeyPressed, key, mods);
            eventDispatcher->Dispatch(event);
        }
        else if (action == GLFW_RELEASE) {
            KeyboardEvent event(EventType::KeyReleased, key, mods);
            eventDispatcher->Dispatch(event);
        }
    }

private:
    static EventDispatcher* eventDispatcher;
};

// Static member initialization
double Mouse::xpos = 0;
double Mouse::ypos = 0;
bool Mouse::buttons[3] = { false, false, false };
EventDispatcher* Mouse::eventDispatcher = nullptr;
EventDispatcher* Keyboard::eventDispatcher = nullptr;
