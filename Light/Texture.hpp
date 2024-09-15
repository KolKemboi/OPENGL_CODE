#pragma once

#include "Shader.hpp"
#include <glad/glad.h>
#include <stb/stb_image.h>

class Texture
{
public:
	Texture(const char* image_name, GLenum TexType, GLenum Slot, GLenum Format, GLenum PixelType);
	~Texture();
	void texUni(Shader& shader, const char* uniform, unsigned int Unit);
	void Bind();
	void Unbind();
private:
	GLenum type;
	unsigned int texture;
};

Texture::Texture(const char* image_name, GLenum TexType, GLenum Slot, GLenum Format, GLenum PixelType)
{
	this->type = TexType;
	int widthImg, heightImg, NumColCh;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* bytes = stbi_load(image_name, &widthImg, &heightImg, &NumColCh, 0);
	
	glGenTextures(1, &this->texture);
	glActiveTexture(Slot);
	glBindTexture(TexType, this->texture);

	glTexParameteri(TexType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(TexType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(TexType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(TexType, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexImage2D(TexType, 0, GL_RGBA, widthImg, heightImg, 0, Format, PixelType, bytes);

	glGenerateMipmap(TexType);
	glBindTexture(TexType, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->texture);
}

void Texture::texUni(Shader& shader, const char* uniform, unsigned int Unit)
{
	unsigned int texUni = glGetUniformLocation(shader.ShaderProgram, uniform);
	shader.UseShader();
	glUniform1i(texUni, Unit);
}

void Texture::Bind()
{
	glBindTexture(this->type, this->texture);
}

void Texture::Unbind()
{
	glBindTexture(this->type, 0);
}
