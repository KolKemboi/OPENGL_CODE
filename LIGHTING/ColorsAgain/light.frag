#version 330 core

out vec4 FragColor;

uniform mat4 lightColor;
in vec3 vertColor;

void main()
{
	FragColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);
}