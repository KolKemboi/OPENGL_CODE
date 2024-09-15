#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include "Shader.hpp"
#include <iostream>

class Texture
{
public:
	Texture(const char* im_name, GLenum TexType, unsigned int Slot, GLenum Format, GLenum PixelType);
	void TexUni(Shader& Shader, const char* uniform, unsigned int unit);
	void Bind();
	void Unbind();
	~Texture();


private:
	unsigned int texture, unit;
	GLenum type;
};

Texture::Texture(const char* im_name, GLenum TexType, unsigned int Slot, GLenum Format, GLenum PixelType)
{
	this->type = TexType;

	int widthImg, heightImg, NumColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(im_name, &widthImg, &heightImg, &NumColCh, 0);

	glGenTextures(1, &this->texture);
	glActiveTexture(GL_TEXTURE0 + Slot);
	this->unit = Slot;
	glBindTexture(TexType, this->texture);

	glTexParameteri(TexType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(TexType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(TexType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(TexType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(TexType, 0, GL_RGBA, widthImg, heightImg, 0, Format, PixelType, bytes);
	glGenerateMipmap(TexType);

	stbi_image_free(bytes);

	glBindTexture(TexType, 0);
}

void Texture::TexUni(Shader& shader, const char* uniform, unsigned int unit)
{
	unsigned int texUni = glGetUniformLocation(shader.ShaderProgram, uniform);
	shader.UseShader();
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + this->unit);
	glBindTexture(this->type, this->texture);
}

void Texture::Unbind()
{
	glBindTexture(this->type, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->texture);
}