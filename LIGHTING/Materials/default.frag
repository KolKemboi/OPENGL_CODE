#version 330 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 Norm;
in vec3 vertColor;
in vec3 crntPos;

uniform vec3 camPos;
uniform Material material;
uniform Light light;

void main()
{
    // Ambient lighting
    vec3 ambient = light.ambient * material.ambient;

    // Diffuse lighting
    vec3 normal = normalize(Norm);
    vec3 lightDir = normalize(light.position - crntPos);
    float diff = max(dot(normal, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    // Specular lighting
    vec3 viewDir = normalize(camPos - crntPos);
    vec3 reflectionDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectionDir), 0.0f), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    // Final color
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0f);
}
