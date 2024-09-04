#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
layout (location = 2) in vec2 tex;
layout (location = 3) in vec3 norm;

out vec3 Color;
out vec3 Norm;
out vec2 TextCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position = vec4(pos, 1.0);
	Color = col;
	TexCoord = tex;
	Norm = norm;
}