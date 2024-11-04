#pragma once 
#include <glm/glm.hpp>

typedef unsigned int u_int;

const char* vertexSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

void main()
{
    gl_Position = vec4(aPos, 1.0);
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

    }

    u_int retShader() const { return m_Shader; }
private:
    u_int m_Shader, m_VertShader, m_FragShader;
};