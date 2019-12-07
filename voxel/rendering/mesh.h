#pragma once
#include "gl/buffer.h"
#include <memory>

using std::unique_ptr;

class Mesh {
public:
	Mesh() = default;
	Mesh(vector<gl::Vertex>& vertices);
	Mesh(vector<gl::Vertex>& vertices, vector<unsigned int>& indices);

	void bind() const;
	void set_vertices(vector<gl::Vertex>& vertices);
	void set_indices(vector<unsigned int>& indices);

	void generate_indices();
	
	int get_index_count() const;

protected:
	unique_ptr<gl::ArrayBuffer> _buffer;
	unique_ptr<gl::IndexBuffer> _ibuffer;
	unique_ptr<gl::VertexArray> _vao;
};