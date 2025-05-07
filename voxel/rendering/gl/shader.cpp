#include "shader.h"
#include <utils/fileio.h>

#define GL_VERSION_4_6
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

const string gl::get_type_str(ShaderType type)
{
	switch (type) {
	case VertexS: return "Vertex"; break;
	case FragmentS:  return "Fragment"; break;
	case GeometryS:  return "Geometry"; break;
	case ComputeS:  return "Compute"; break;
	}
}

gl::Shader::Shader()
{
	_shaderId = glCreateProgram();
}

gl::Shader::~Shader()
{
	glDeleteProgram(_shaderId);
}

void gl::Shader::attach(const string filename, ShaderType type)
{
	File shaderFile(filename);
	
	string shaderSource = shaderFile.read();
	const char* source = shaderSource.c_str();

	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	compile_errors(shader, type);

	glAttachShader(_shaderId, shader);
	glDeleteShader(shader);
	shaderFile.close();
}

void gl::Shader::build()
{
	glLinkProgram(_shaderId);

	int success;
	char infoLog[1024];
	glGetProgramiv(_shaderId, GL_LINK_STATUS, &success);
	
	if (!success)
	{
		glGetProgramInfoLog(_shaderId, 1024, NULL, infoLog);
		std::cout << "[ERROR] Shader program failed to compile!: " << "\n";
		std::cout << infoLog;
		std::cout << "\n --------------------------------------------------------- " << std::endl;
	}
}

void gl::Shader::bind() const
{
	glUseProgram(_shaderId);
	glUniform1i(glGetUniformLocation(_shaderId, "textureArray"), 0);
}

void gl::Shader::unbind() const
{
	glUseProgram(0);
}

void gl::Shader::set_int(const string name, int value)
{
	int uniform_loc = glGetUniformLocation(_shaderId, name.c_str());
	glUniform1i(uniform_loc, value);
}

void gl::Shader::set_float(const string name, float value)
{
	int uniform_loc = glGetUniformLocation(_shaderId, name.c_str());
	glUniform1f(uniform_loc, value);
}

void gl::Shader::set_vec2(const string name, glm::vec2 value)
{
	int uniform_loc = glGetUniformLocation(_shaderId, name.c_str());
	glUniform2f(uniform_loc, value.x, value.y);
}

void gl::Shader::set_vec3(const string name, glm::vec3 value)
{
	int uniform_loc = glGetUniformLocation(_shaderId, name.c_str());
	glUniform3f(uniform_loc, value.x, value.y, value.z);
}

void gl::Shader::set_mat3(const string name, glm::mat3 value)
{
	int uniform_loc = glGetUniformLocation(_shaderId, name.c_str());
	glUniformMatrix3fv(uniform_loc, 1, GL_FALSE, glm::value_ptr(value));
}

void gl::Shader::set_mat4(const string name, glm::mat4 value)
{
	int uniform_loc = glGetUniformLocation(_shaderId, name.c_str());
	glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, glm::value_ptr(value));
}

void gl::Shader::compile_errors(unsigned int shader, ShaderType type)
{
	int success;
	char infoLog[1024];
	
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		std::cout << "[ERROR] " << get_type_str(type) << " shader failed to compile!: " << "\n";
		std::cout << infoLog;
		std::cout << "\n --------------------------------------------------------- " << std::endl;
	}
}
