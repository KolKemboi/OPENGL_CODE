#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 vertColor;
out vec3 crntPos;
out vec3 Norm;


void main()
{
	crntPos = vec3( model * vec4(position, 1.0f));
	gl_Position = proj * view * vec4(crntPos, 1.0);

	
	vertColor = color;
	Norm = normal;
}


