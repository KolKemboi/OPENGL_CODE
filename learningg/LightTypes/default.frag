#version 330 core

out vec4 FragColor;

in vec3 vertColor;
in vec3 vertNorm;
in vec2 TexCoord;
in vec3 crntPos;

uniform sampler2D tex0;
uniform sampler2D tex1;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
	float ambient = 0.20f;

	//diffuse lighting
	vec3 normal = normalize(vertNorm);
	vec3 lightDir = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDir), 0.0f);

	//specular
	float specLight = 0.5f;
	vec3 viewDir = normalize(camPos - crntPos);
	vec3 reflectionDir = reflect(-lightDir, normal);
	float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 16);
	float specular = specAmount * specLight;

	FragColor = (texture(tex0, TexCoord) * (diffuse + ambient) +  specular) * lightColor;
	//FragColor = texture(tex0, TexCoord);

}