#version 330 core

out vec4 FragColor;

in vec3 Normals;

uniform sampler2D texture_diffuse1;

float near = 0.1;
float far = 100.0f;

float LinearizeDepth(float depth)
{
	float z = depth * 2.0 - 1.0;
	return (2.0 * near * far ) / (far + near - z * (far - near));
}

void main()
{
	float depth = LinearizeDepth(gl_FragCoord.z) / far;
	//FragColor = vec4(vec3(depth), 1.0f);
	FragColor = vec4(Normals, 1.0f);
}