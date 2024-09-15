#version 330 core

out vec4 FragColor;

in vec3 vertColor;
in vec2 TexCoord;
in vec3 vertNorm;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

void main()
{
	//FragColor = texture(diffuse0, TexCoord);
	FragColor = vec4(vertColor, 1.0f);
}