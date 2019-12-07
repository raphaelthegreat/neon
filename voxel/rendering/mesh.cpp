#include "mesh.h"

Mesh::Mesh(vector<gl::Vertex>& vertices)
{
	_vao = std::make_unique<gl::VertexArray>();

	_buffer = std::make_unique<gl::ArrayBuffer>(vertices);
	_ibuffer = std::make_unique<gl::IndexBuffer>();

	_vao->add_vbo(*_buffer);
	_vao->add_ibo(*_ibuffer);
}

Mesh::Mesh(vector<gl::Vertex>& vertices, vector<unsigned int>& indices)
{
	_vao = std::make_unique<gl::VertexArray>();

	_buffer = std::make_unique<gl::ArrayBuffer>(vertices);
	_ibuffer = std::make_unique<gl::IndexBuffer>(indices);

	_vao->add_vbo(*_buffer);
	_vao->add_ibo(*_ibuffer);
}

void Mesh::bind() const
{
	_vao->bind();
}

void Mesh::set_vertices(vector<gl::Vertex>& vertices)
{
	_buffer->set_data(vertices);
}

void Mesh::set_indices(vector<unsigned int>& indices)
{
	_ibuffer->set_data(indices);
}

void Mesh::generate_indices()
{
	vector<unsigned int> indices;
	indices.reserve(_buffer->get_count());

	for (int i = 0; i < _buffer->get_count(); i++) {
		indices.push_back(static_cast<unsigned int>(i));
	}

	_ibuffer->set_data(indices);
}

int Mesh::get_index_count() const
{
	return _ibuffer->get_count();
}

