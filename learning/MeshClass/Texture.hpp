#pragma once

#include "Shader.hpp"
#include <glad/glad.h>
#include <stb/stb_image.h>

class Texture
{
public:
	Texture(const char* im_name, const char* TexType, unsigned int Slot, GLenum Format, GLenum PixelType);
	void TexUniform(Shader& shader, const char* uniform, unsigned int unit);
	void Bind();
	void Unbind();
	~Texture();
	const char* get_type()
	{
		return  this->type;
	}

private:
	unsigned int texture, unit;
	const char* type;
};

Texture::Texture(const char* im_name, const char* TexType, unsigned int Slot, GLenum Format, GLenum PixelType)
{
	this->type = TexType;
	this->unit = Slot;

    int widthImg, heightImg, NumColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(im_name, &widthImg, &heightImg, &NumColCh, 0);
	if (bytes == nullptr)
	{
		std::cerr << "Failed to load texture: " << im_name << std::endl;
	}


	glGenTextures(1, &this->texture);
	glActiveTexture(GL_TEXTURE0 + Slot);
	glBindTexture(GL_TEXTURE_2D, this->texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, Format, PixelType, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Texture::TexUniform(Shader& shader, const char* uniform, unsigned int unit)
{
	shader.UseShader();
	glUniform1i(glGetUniformLocation(shader.ShaderProgram, uniform), unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + this->unit);
	glBindTexture(GL_TEXTURE_2D, this->texture);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->texture);
}