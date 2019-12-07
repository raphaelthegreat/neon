#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace gl {

class Shader;
class Texture2D {
public:
	Texture2D(const string path);
	~Texture2D();

	int width() const;
	int height() const;
	int channels() const;

	void bind(unsigned int slot = 0);
	void unbind();

protected:
	unsigned int _textureId = 0;
	int _width = 0;
	int _height = 0;
	int _channels = 0;
};

class TextureArray {
public:
	TextureArray(gl::Shader* shader, vector<string>& paths);
	~TextureArray() = default;

	int width() const;
	int height() const;
	int channels() const;

	void bind(unsigned int slot = 0);
	void unbind();

protected:
	unsigned int _textureId = 0;
	int _width = 0;
	int _height = 0;
	int _channels = 0;
};

}