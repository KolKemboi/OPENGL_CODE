#pragma once 
#include <glm/glm.hpp>

typedef unsigned int u_int;

const char* vertexSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    color = aColor;
}

)";



const char* fragmentSource = R"(
#version 330 core
out vec4 FragColor;

in vec3 color;

void main()
{
    FragColor = vec4(color, 1.0);
}

)";

class Shader
{
public:
    Shader()
    {
        m_VertShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(m_VertShader, 1, &vertexSource, NULL);
        glCompileShader(m_VertShader);

        m_FragShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(m_FragShader, 1, &fragmentSource, NULL);
        glCompileShader(m_FragShader);

        m_Shader = glCreateProgram();
        glAttachShader(m_Shader, m_VertShader);
        glAttachShader(m_Shader, m_FragShader);
        glLinkProgram(m_Shader);

        glDeleteShader(m_FragShader);
        glDeleteShader(m_VertShader);

    }

    void DestroyShader()
    {
        glDeleteProgram(m_Shader);
        m_FragShader = 0;
        m_VertShader = 0;
        m_Shader = 0;
    }

    u_int retShader() const { return m_Shader; }

    void useShader() const { glUseProgram(m_Shader); }
private:
    u_int m_Shader, m_VertShader, m_FragShader;
};