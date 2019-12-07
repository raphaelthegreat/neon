#pragma once
#include "gl/shader.h"
#include "gl/texture.h"
#include <memory>

using std::unique_ptr;

class Material {
public:
	Material(const string& texture, const string& v_path,
								    const string& f_path,
								    const string& g_path = "",
								    const string& c_path = "");
	
	Material(vector<string> textures, const string& v_path,
								      const string& f_path,
								      const string& g_path = "",
								      const string& c_path = "");

	~Material() = default;

	void set_texture(const string& path);
	void set_texture_array(vector<string>& paths);

	void set_shader(const string& v_path,
					const string& f_path,
					const string& g_path = "",
					const string& c_path = "");

	void bind(int texture_slot = 0) const;
	void unbind() const;

	gl::Shader& get_shader();
	gl::Texture2D& get_texture();

protected:
	unique_ptr<gl::Texture2D> _texture;
	unique_ptr<gl::TextureArray> _texture_array;

	unique_ptr<gl::Shader> _shader;

	bool tex_array;
};