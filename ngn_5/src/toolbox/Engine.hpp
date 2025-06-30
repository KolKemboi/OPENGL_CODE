#pragma once

#include <iostream>
#ifndef _GLAD_GUARD__
#include <glad/glad.h>
#endif 
#include <GLFW/glfw3.h>

class Engine{
public:
	Engine();
	~Engine();
	void runEngine();
private:
	unsigned int m_Width, m_Height;
	GLFWwindow* m_Window;

private:
	void closeWindow(GLFWwindow*);
};
