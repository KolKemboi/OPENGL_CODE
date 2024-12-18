#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform float outlineThickness;

void main()
{
	vec3 offset = aPos + aNorm * outlineThickness;

	gl_Position = projection * view * model * vec4(offset, 1.0f);
}
