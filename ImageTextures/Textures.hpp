#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include "Shader.hpp"

class Texture
{
public:
	Texture(const char* image, GLenum TexType, GLenum Slot, GLenum Format, GLenum PixelType);
	~Texture();
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
private:
	unsigned int texture;
	GLenum type;
};

Texture::Texture(const char* image, GLenum TexType, GLenum Slot, GLenum Format, GLenum PixelType)
{
	this->type = TexType;
	int widthImg, heightImg, numColCh;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	glGenTextures(1, &this->texture);
	glActiveTexture(Slot);
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

Texture::~Texture()
{
	glDeleteTextures(1, &this->texture);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	unsigned int texUni = glGetUniformLocation(shader.ShaderProgram, uniform);
	shader.useShader();
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glBindTexture(this->type, this->texture);
}

void Texture::Unbind()
{
	glBindTexture(this->type, 0);

}
