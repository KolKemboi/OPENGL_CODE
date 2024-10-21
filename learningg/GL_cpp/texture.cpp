#include "texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
	type = texType;
	int widthImg, heightImg, numCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numCh, 0);


	glGenTextures(1, &texture);
	glActiveTexture(slot);
	glBindTexture(texType, texture);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glTexImage2D(texType, 0, GL_RGB, widthImg, heightImg, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);
	stbi_image_free(bytes);


	
}
void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
	GLuint tex0Uni = glGetUniformLocation(shader.shaderProg, "tex0");
	shader.Activate();
	glUniform1i(tex0Uni, unit);

}

void Texture::Bind() {
	glBindTexture(type, texture);

}
void Texture::Unbind() {
	glBindTexture(type, 0);

}

void Texture::Delete() {
	glDeleteTextures(1 ,&type);
}