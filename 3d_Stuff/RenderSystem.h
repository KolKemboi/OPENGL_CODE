#pragma once 


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "MeshLoader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

typedef unsigned int u_int;

class RenderSystem
{
public:
	void initScene()
	{
		glClearColor(0.2, 0.1, 0.3, 1.0);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void Render(Mesh& mesh, Camera& camera, u_int width, u_int height)
	{
		mesh.m_Shader.useShader();
		setModelMat(mesh);
		camera.SetView(mesh);
		camera.SetProjection(mesh, width, height);
		glBindVertexArray(mesh.m_VertexArray);
		glDrawElements(GL_TRIANGLES, mesh.m_indexCount, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}
	void clearScene(GLFWwindow* window)
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void setModelMat(Mesh& mesh)
	{
		// Reset the model matrix
		this->m_ModelMat = glm::mat4(1.0f);

		// Apply transformations: Position, Rotation, and Scale
		this->m_ModelMat = glm::translate(this->m_ModelMat, mesh.m_Transform.m_Position);
		//this->m_ModelMat = glm::rotate(this->m_ModelMat, glm::radians(mesh.m_Transform.m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate around X
		//this->m_ModelMat = glm::rotate(this->m_ModelMat, glm::radians(mesh.m_Transform.m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around Y
		//this->m_ModelMat = glm::rotate(this->m_ModelMat, glm::radians(mesh.m_Transform.m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around Z
		this->m_ModelMat = glm::scale(this->m_ModelMat, mesh.m_Transform.m_Scale); // Apply scaling

		// Set the model matrix uniform in the shader
		glUniformMatrix4fv(glGetUniformLocation(mesh.m_Shader.retShader(), "model"), 1, GL_FALSE, glm::value_ptr(this->m_ModelMat));
	}

private:

	glm::mat4 m_ModelMat = glm::mat4(1.0);
};
