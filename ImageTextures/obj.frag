#version 330 core

out vec4 FragColor;

in vec3 Color;
in vec3 Norm;
in vec2 TexCoord;

uniform sampler2D tex0;

void main()
{
	FragColor = texture(tex0, TexCoord);
}