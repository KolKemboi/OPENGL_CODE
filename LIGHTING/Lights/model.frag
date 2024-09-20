#version 330 core

out vec4 FragColor;

in vec3 Normals;

uniform sampler2D texture_diffuse1;

void main()
{
	FragColor = vec4(Normals, 1.0f);
}