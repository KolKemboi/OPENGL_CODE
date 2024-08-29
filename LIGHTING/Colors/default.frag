#version 330 core

out vec4 FragColor;

in vec3 Norm;
in vec3 vertColor;
in vec3 crntPos;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;


void main()
{
	float ambient = 0.2f;

	//diffuse
	vec3 normal = normalize(Norm);
	vec3 lightDir = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDir), 0.0f);

	//specular
	float specularLight = 0.50f;
	vec3 viewDir = normalize(camPos - crntPos);
	vec3 reflectionDir = reflect(-lightDir, normal);
	float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 8);
	float specular = specAmount * specularLight;


	FragColor = lightColor * vec4( vertColor, 1.0f) * (diffuse + ambient + specular);
}