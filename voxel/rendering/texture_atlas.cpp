#include "texture_atlas.h"

TextureAtlas::TextureAtlas(const string path) :
	_texture(path)
{
	_texture_size = 16;
}

std::array<float, 8> TextureAtlas::get_texture(float x, float y)
{
	glm::vec2 coords = glm::vec2(x, y);
	
	float tex_per_row = width() / _texture_size;
	float indv_tex_size = 1.0f / tex_per_row;
	float pixel_size = 1.0f / width();

	float xMin = (coords.x * indv_tex_size) + 0.5f * pixel_size;
	float yMin = (coords.y * indv_tex_size) + 0.5f * pixel_size;

	float xMax = (xMin + indv_tex_size) - pixel_size;
	float yMax = (yMin + indv_tex_size) - pixel_size;

	return
	{
		xMax, yMax,
		xMin, yMax,
		xMin, yMin,
		xMax, yMin
	};
}

int TextureAtlas::width() const
{
	return _texture.width();
}

int TextureAtlas::height() const
{
	return _texture.height();
}

int TextureAtlas::channels() const
{
	return _texture.channels();
}

void TextureAtlas::bind(unsigned int slot)
{
	_texture.bind();
}

void TextureAtlas::unbind()
{
	_texture.unbind();
}
