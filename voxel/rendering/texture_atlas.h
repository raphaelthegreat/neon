#pragma once
#include <array>
#include <glm/glm.hpp>
#include "gl/texture.h"

class TextureAtlas {
public:
	TextureAtlas(const string path);

	int width() const;
	int height() const;
	int channels() const;

	void bind(unsigned int slot = 0);
	void unbind();

	std::array<float, 8> get_texture(float x, float y);

protected:
	gl::Texture2D _texture;
	float _texture_size;
};