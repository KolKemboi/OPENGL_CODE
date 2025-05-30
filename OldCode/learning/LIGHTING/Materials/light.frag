#version 330 core

out vec4 FragColor;

uniform vec3 lightColor;

in vec3 vertColor;

void main()
{
	FragColor = vec4(lightColor, 1.0f);
}