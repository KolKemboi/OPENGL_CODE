#version 330 core

out vec4 FragColor;

in vec3 vertColor;
in vec3 vertNorm;
in vec2 TexCoord;
uniform sampler2D tex0;

void main()
{
	FragColor = vec4(vertColor, 1.0f);
	//FragColor = texture(tex0, TexCoord)
}