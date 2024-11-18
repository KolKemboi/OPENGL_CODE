#version 330 core

out vec4 FragColor;

in vec3 vertColor;
in vec3 vertNorm;

void main()
{
	FragColor = vec4(vertColor, 1.0f);
}