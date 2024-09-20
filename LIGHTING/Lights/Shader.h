#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

class Shader
{
public:
	unsigned int ShaderProgram;

	Shader(const char* vertFile, const char* fragFile)
	{
		std::string vertexCode, fragmentCode; //creating place to store the files
		std::ifstream vShaderFile, fShaderFile; // file reader

		//checks for exceptions in the file
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vShaderFile.open(vertFile);
			fShaderFile.open(fragFile);
			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

		}
		catch (std::ifstream::failure& e)
		{
			std::cerr << "ERROR::SHADER::FILE_NOT_LOADED:: " << e.what() << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(this->vertexShader, 1, &vShaderCode, NULL);
		glCompileShader(this->vertexShader);
		CheckCompileErrors(this->vertexShader, "VERTEX");


		this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(this->fragmentShader, 1, &fShaderCode, NULL);
		glCompileShader(this->fragmentShader);
		CheckCompileErrors(this->fragmentShader, "FRAGMENT");

		this->ShaderProgram = glCreateProgram();
		glAttachShader(this->ShaderProgram, this->vertexShader);
		glAttachShader(this->ShaderProgram, this->fragmentShader);
		glLinkProgram(this->ShaderProgram);
		CheckCompileErrors(this->ShaderProgram, "PROGRAM");

		glDeleteShader(this->fragmentShader);
		glDeleteShader(this->vertexShader);

	}
	~Shader()
	{
		glDeleteProgram(this->ShaderProgram);
	}

	void UseShader()
	{
		glUseProgram(this->ShaderProgram);
	}



	// Set uniform functions with corrected names
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(this->ShaderProgram, name.c_str()), (int)value);
	}

	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(this->ShaderProgram, name.c_str()), value);
	}

	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(this->ShaderProgram, name.c_str()), value);
	}

	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(this->ShaderProgram, name.c_str()), 1, &value[0]);
	}

	void setVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(this->ShaderProgram, name.c_str()), x, y);
	}

	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(this->ShaderProgram, name.c_str()), 1, &value[0]);
	}

	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(this->ShaderProgram, name.c_str()), x, y, z);
	}

	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(this->ShaderProgram, name.c_str()), 1, &value[0]);
	}

	void setVec4(const std::string& name, float x, float y, float z, float w) const
	{
		glUniform4f(glGetUniformLocation(this->ShaderProgram, name.c_str()), x, y, z, w);
	}

	void setMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(this->ShaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);  // Correct function
	}

	void setMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(this->ShaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);  // Correct function
	}

	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(this->ShaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);  // Correct function
	}


private:
	unsigned int vertexShader, fragmentShader;


	void CheckCompileErrors(unsigned int shader, const std::string& type)
	{
		int success;
		char infoLog[1024];

		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n---------------------------" << std::endl;
			}

		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cerr << "ERROR::SHADER_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n---------------------------" << std::endl;
			}

		}



	}

};
