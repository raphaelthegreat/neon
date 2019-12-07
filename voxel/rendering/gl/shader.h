#pragma once
#include <string>
#include <glm/glm.hpp>

using std::string;

namespace gl {

enum ShaderType {
	VertexS = 0x8B31,
	FragmentS = 0x8B30,
	GeometryS = 0x8DD9,
	ComputeS = 0x91B2
};

const string get_type_str(ShaderType type);

class Shader {
public:
	friend class TextureArray;

public:
	Shader();
	~Shader();

	void attach(const string filename, ShaderType type);
	void build();

	void bind() const;
	void unbind() const;

	void set_int(const string name, int value);
	void set_float(const string name, float value);
	void set_vec2(const string name, glm::vec2 value);
	void set_vec3(const string name, glm::vec3 value);
	void set_mat3(const string name, glm::mat3 value);
	void set_mat4(const string name, glm::mat4 value);

protected:
	void compile_errors(unsigned int shader, ShaderType type);

protected:
	unsigned int _shaderId = 0;
};

}