#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCood;
layout (location = 3) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 vertColor;
out vec2 TexCoord;
out vec3 vertNorm;
out vec4 crntPos;

void main()
{
	gl_Position = proj * view * model * vec4(position, 1.0);
	vertColor = color;
	TexCoord = texCood;
	vertNorm = normal;
}
