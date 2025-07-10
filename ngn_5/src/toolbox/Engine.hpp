#pragma once

#include <iostream>
#include <memory>
#ifndef _GLAD_GUARD__
#include <glad/glad.h>
#endif 
#include <GLFW/glfw3.h>
#include "Model.hpp"

class Engine{
public:
	Engine();
	~Engine();
	void runEngine();
private:
	unsigned int m_Width, m_Height;
	GLFWwindow* m_Window;
	std::shared_ptr<Model> m_Model;

private:
	void closeWindow(GLFWwindow*);
};
