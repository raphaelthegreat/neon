#include "material.h"

Material::Material(const string& texture, const string& v_path, 
										 const string& f_path, 
										 const string& g_path, 
										 const string& c_path)
{
	_texture = std::make_unique<gl::Texture2D>(texture);
	_shader = std::make_unique<gl::Shader>();
	
	tex_array = false;

	_shader->attach(v_path, gl::VertexS);
	_shader->attach(f_path, gl::FragmentS);
	if (!g_path.empty()) _shader->attach(g_path, gl::GeometryS);
	if (!c_path.empty()) _shader->attach(c_path, gl::ComputeS);

	_shader->build();
}

Material::Material(vector<string> textures, const string& v_path, const string& f_path, const string& g_path, const string& c_path)
{
	_shader = std::make_unique<gl::Shader>();

	tex_array = true;

	_shader->attach(v_path, gl::VertexS);
	_shader->attach(f_path, gl::FragmentS);
	if (!g_path.empty()) _shader->attach(g_path, gl::GeometryS);
	if (!c_path.empty()) _shader->attach(c_path, gl::ComputeS);

	_shader->build();
	_texture_array = std::make_unique<gl::TextureArray>(_shader.get(), textures);
}

void Material::set_texture(const string& path)
{
	_texture.reset();
	_texture = std::make_unique<gl::Texture2D>(path);
}

void Material::set_texture_array(vector<string>& paths)
{
	_texture.reset();
	_texture_array = std::make_unique<gl::TextureArray>(_shader.get(), paths);
}

void Material::set_shader(const string& v_path, 
						  const string& f_path, 
						  const string& g_path, 
						  const string& c_path)
{
	_shader.reset();
	_shader = std::make_unique<gl::Shader>();

	_shader->attach(v_path, gl::VertexS);
	_shader->attach(f_path, gl::FragmentS);
	if (!g_path.empty()) _shader->attach(g_path, gl::GeometryS);
	if (!c_path.empty()) _shader->attach(c_path, gl::ComputeS);

	_shader->build();
}

void Material::bind(int slot) const
{
	_shader->bind();

	if (tex_array)
		_texture_array->bind(slot);
	else
		_texture->bind(slot);
}

void Material::unbind() const
{
	_shader->unbind();

	if (tex_array)
		_texture_array->unbind();
	else
		_texture->unbind();
}

gl::Shader& Material::get_shader()
{
	return *_shader;
}

gl::Texture2D& Material::get_texture()
{
	return *_texture;
}
