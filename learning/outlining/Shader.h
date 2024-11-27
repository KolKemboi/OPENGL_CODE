#pragma once

class Shader
{
public:
	Shader(const char* vertexFile, const char* fragFile)
	{

	}
	~Shader();

private:

};



class ModelShader : public Shader
{
public:
	ModelShader()
	{
		Shader shader("/shader", "/Shader");
	}
};

class LightShader : public Shader
{
public:
	LightShader()
	{
		Shader shader("/shader", "/Shader");
	}

};