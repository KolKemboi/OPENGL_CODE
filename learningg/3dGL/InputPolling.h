#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Inputs
{
public:
    Inputs(GLFWwindow* window)
    {
        this->window = window;
        instance = this;
        std::fill(std::begin(keys), std::end(keys), false); 
    }

    void destroyClass()
    {
        if (instance == this)
            instance = nullptr;
    }

    void Callback()
    {
        glfwSetKeyCallback(window, keyCallback);
    }

    std::string keyPressed()
    {
        if (instance) {
            // Check for letters A-Z
            if (instance->keys[GLFW_KEY_A]) return "A";
            if (instance->keys[GLFW_KEY_B]) return "B";
            if (instance->keys[GLFW_KEY_C]) return "C";
            if (instance->keys[GLFW_KEY_D]) return "D";
            if (instance->keys[GLFW_KEY_E]) return "E";
            if (instance->keys[GLFW_KEY_F]) return "F";
            if (instance->keys[GLFW_KEY_G]) return "G";
            if (instance->keys[GLFW_KEY_H]) return "H";
            if (instance->keys[GLFW_KEY_I]) return "I";
            if (instance->keys[GLFW_KEY_J]) return "J";
            if (instance->keys[GLFW_KEY_K]) return "K";
            if (instance->keys[GLFW_KEY_L]) return "L";
            if (instance->keys[GLFW_KEY_M]) return "M";
            if (instance->keys[GLFW_KEY_N]) return "N";
            if (instance->keys[GLFW_KEY_O]) return "O";
            if (instance->keys[GLFW_KEY_P]) return "P";
            if (instance->keys[GLFW_KEY_Q]) return "Q";
            if (instance->keys[GLFW_KEY_R]) return "R";
            if (instance->keys[GLFW_KEY_S]) return "S";
            if (instance->keys[GLFW_KEY_T]) return "T";
            if (instance->keys[GLFW_KEY_U]) return "U";
            if (instance->keys[GLFW_KEY_V]) return "V";
            if (instance->keys[GLFW_KEY_W]) return "W";
            if (instance->keys[GLFW_KEY_X]) return "X";
            if (instance->keys[GLFW_KEY_Y]) return "Y";
            if (instance->keys[GLFW_KEY_Z]) return "Z";

            // Check for numbers 0-9
            if (instance->keys[GLFW_KEY_0]) return "0";
            if (instance->keys[GLFW_KEY_1]) return "1";
            if (instance->keys[GLFW_KEY_2]) return "2";
            if (instance->keys[GLFW_KEY_3]) return "3";
            if (instance->keys[GLFW_KEY_4]) return "4";
            if (instance->keys[GLFW_KEY_5]) return "5";
            if (instance->keys[GLFW_KEY_6]) return "6";
            if (instance->keys[GLFW_KEY_7]) return "7";
            if (instance->keys[GLFW_KEY_8]) return "8";
            if (instance->keys[GLFW_KEY_9]) return "9";

            // Check for function keys F1-F12
            if (instance->keys[GLFW_KEY_F1]) return "F1";
            if (instance->keys[GLFW_KEY_F2]) return "F2";
            if (instance->keys[GLFW_KEY_F3]) return "F3";
            if (instance->keys[GLFW_KEY_F4]) return "F4";
            if (instance->keys[GLFW_KEY_F5]) return "F5";
            if (instance->keys[GLFW_KEY_F6]) return "F6";
            if (instance->keys[GLFW_KEY_F7]) return "F7";
            if (instance->keys[GLFW_KEY_F8]) return "F8";
            if (instance->keys[GLFW_KEY_F9]) return "F9";
            if (instance->keys[GLFW_KEY_F10]) return "F10";
            if (instance->keys[GLFW_KEY_F11]) return "F11";
            if (instance->keys[GLFW_KEY_F12]) return "F12";

            // Check for common special keys
            if (instance->keys[GLFW_KEY_SPACE]) return "Space";
            if (instance->keys[GLFW_KEY_ENTER]) return "Enter";
            if (instance->keys[GLFW_KEY_BACKSPACE]) return "Backspace";
            if (instance->keys[GLFW_KEY_TAB]) return "Tab";
            if (instance->keys[GLFW_KEY_ESCAPE]) return "Escape";
            if (instance->keys[GLFW_KEY_LEFT_SHIFT] || instance->keys[GLFW_KEY_RIGHT_SHIFT]) return "Shift";
            if (instance->keys[GLFW_KEY_LEFT_CONTROL] || instance->keys[GLFW_KEY_RIGHT_CONTROL]) return "Control";
            if (instance->keys[GLFW_KEY_LEFT_ALT] || instance->keys[GLFW_KEY_RIGHT_ALT]) return "Alt";

            // Check for arrow keys
            if (instance->keys[GLFW_KEY_LEFT]) return "Left Arrow";
            if (instance->keys[GLFW_KEY_RIGHT]) return "Right Arrow";
            if (instance->keys[GLFW_KEY_UP]) return "Up Arrow";
            if (instance->keys[GLFW_KEY_DOWN]) return "Down Arrow";

            // Check for punctuation and other symbols
            if (instance->keys[GLFW_KEY_COMMA]) return ",";
            if (instance->keys[GLFW_KEY_PERIOD]) return ".";
            if (instance->keys[GLFW_KEY_SLASH]) return "/";
            if (instance->keys[GLFW_KEY_SEMICOLON]) return ";";
            if (instance->keys[GLFW_KEY_APOSTROPHE]) return "'";
            if (instance->keys[GLFW_KEY_LEFT_BRACKET]) return "[";
            if (instance->keys[GLFW_KEY_RIGHT_BRACKET]) return "]";
            if (instance->keys[GLFW_KEY_MINUS]) return "-";
            if (instance->keys[GLFW_KEY_EQUAL]) return "=";
            if (instance->keys[GLFW_KEY_BACKSLASH]) return "\\";
            if (instance->keys[GLFW_KEY_GRAVE_ACCENT]) return "`";

            // Check for other useful keys
            if (instance->keys[GLFW_KEY_INSERT]) return "Insert";
            if (instance->keys[GLFW_KEY_DELETE]) return "Delete";
            if (instance->keys[GLFW_KEY_HOME]) return "Home";
            if (instance->keys[GLFW_KEY_END]) return "End";
            if (instance->keys[GLFW_KEY_PAGE_UP]) return "Page Up";
            if (instance->keys[GLFW_KEY_PAGE_DOWN]) return "Page Down";

            // Keypad keys
            if (instance->keys[GLFW_KEY_KP_0]) return "Keypad 0";
            if (instance->keys[GLFW_KEY_KP_1]) return "Keypad 1";
            if (instance->keys[GLFW_KEY_KP_2]) return "Keypad 2";
            if (instance->keys[GLFW_KEY_KP_3]) return "Keypad 3";
            if (instance->keys[GLFW_KEY_KP_4]) return "Keypad 4";
            if (instance->keys[GLFW_KEY_KP_5]) return "Keypad 5";
            if (instance->keys[GLFW_KEY_KP_6]) return "Keypad 6";
            if (instance->keys[GLFW_KEY_KP_7]) return "Keypad 7";
            if (instance->keys[GLFW_KEY_KP_8]) return "Keypad 8";
            if (instance->keys[GLFW_KEY_KP_9]) return "Keypad 9";
            if (instance->keys[GLFW_KEY_KP_ADD]) return "Keypad +";
            if (instance->keys[GLFW_KEY_KP_SUBTRACT]) return "Keypad -";
            if (instance->keys[GLFW_KEY_KP_MULTIPLY]) return "Keypad *";
            if (instance->keys[GLFW_KEY_KP_DIVIDE]) return "Keypad /";
            if (instance->keys[GLFW_KEY_KP_ENTER]) return "Keypad Enter";

            // Media and other keys
            if (instance->keys[GLFW_KEY_PRINT_SCREEN]) return "Print Screen";
            if (instance->keys[GLFW_KEY_PAUSE]) return "Pause";
        }
        return ""; // If no key is pressed, return an empty string
    }
private:
    bool keys[1024]; 
    GLFWwindow* window;

    static Inputs* instance;

    static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mode)
    {
        if (instance) 
        {
            if (key >= 0 && key < 1024) 
            {
                if (action == GLFW_PRESS)
                    instance->keys[key] = true;
                else if (action == GLFW_RELEASE)
                    instance->keys[key] = false;
            }
        }
    }
};

Inputs* Inputs::instance = nullptr;
