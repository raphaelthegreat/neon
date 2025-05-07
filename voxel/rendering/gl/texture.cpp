#include "texture.h"
#include <iostream>
#include "shader.h"

#define GL_VERSION_4_6
#include <glad/glad.h>
#include "stb_image.h"

gl::Texture2D::Texture2D(const string path)
{
	stbi_set_flip_vertically_on_load(true);
	
	unsigned char* data = stbi_load(path.c_str(), &_width, &_height, &_channels, 0);
	glGenTextures(1, &_textureId);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "[ERROR] Failed to load texture at path: " << path << std::endl;
	}

	stbi_image_free(data);
}

gl::Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_textureId);
}

int gl::Texture2D::width() const
{
	return _width;
}

int gl::Texture2D::height() const
{
	return _height;
}

int gl::Texture2D::channels() const
{
	return _channels;
}

void gl::Texture2D::bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, _textureId);
}

void gl::Texture2D::unbind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

gl::TextureArray::TextureArray(gl::Shader* shader, vector<string>& paths)
{
	stbi_set_flip_vertically_on_load(true);

	int width, height, channels;

	glActiveTexture(GL_TEXTURE0);

	glGenTextures(1, &_textureId);
	glBindTexture(GL_TEXTURE_2D_ARRAY, _textureId);
	
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	float aniso = 10.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
	glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);

	auto data = stbi_load(paths[0].c_str(), &_width, &_height, &_channels, 0);
	stbi_image_free(data);
	
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGB8, _width, _height, paths.size(), 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)0);

	for (int i = 0; i < paths.size(); i++) {
		auto path = paths[i];
		auto _data = stbi_load(paths[i].c_str(), &width, &height, &channels, 0);
		
		if (_data) {
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, GL_RGB, GL_UNSIGNED_BYTE, _data);
			glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
		}
		else {
			std::cout << "[ERROR] Failed to load texture at path: " << paths[i] << std::endl;
		}

		stbi_image_free(_data);
	}

	shader->bind();
	auto program = shader->_shaderId;

	int location = glGetUniformLocation(program, "layer");
	glProgramUniform1i(program, location, 0);
}

int gl::TextureArray::width() const
{
	return _width;
}

int gl::TextureArray::height() const
{
	return _height;
}

int gl::TextureArray::channels() const
{
	return _channels;
}

void gl::TextureArray::bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D_ARRAY, _textureId);
}

void gl::TextureArray::unbind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}
