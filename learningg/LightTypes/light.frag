#version 330 core

out vec4 FragColor;

uniform vec4 lightColor;
in vec3 vertColor;

void main()
{
	FragColor = lightColor;
}