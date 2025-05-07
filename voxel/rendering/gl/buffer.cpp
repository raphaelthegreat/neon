#include "buffer.h"

#define GL_VERSION_4_6
#include <glad/glad.h>

gl::Vertex::Vertex(glm::vec3 pos, glm::vec3 coord)
{
	position = pos;
	tex_coord = coord;
}

gl::Vertex::Vertex(glm::vec3 pos, glm::vec2 coord)
{
	position = pos;
	tex_coord = glm::vec3(coord.x, coord.y, 0);
}

gl::Vertex::Vertex(float x, float y, float z, float u, float v, float layer)
{
	position = glm::vec3(x, y, z);
	tex_coord = glm::vec3(u, v, layer);
}

gl::ArrayBuffer::ArrayBuffer()
{
	glGenBuffers(1, &_vboId);
	glBindBuffer(GL_ARRAY_BUFFER, _vboId);
}

gl::ArrayBuffer::ArrayBuffer(vector<Vertex>& data)
{
	glGenBuffers(1, &_vboId);
	glBindBuffer(GL_ARRAY_BUFFER, _vboId);

	if (!data.empty()) {
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), &data.front(), GL_STATIC_DRAW);
		_count = static_cast<unsigned int>(data.size());
	}
}

gl::ArrayBuffer::~ArrayBuffer()
{
	glDeleteBuffers(1, &_vboId);
}

void gl::ArrayBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, _vboId);
}

void gl::ArrayBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void gl::ArrayBuffer::set_data(vector<Vertex>& data)
{
	glBindBuffer(GL_ARRAY_BUFFER, _vboId);
	
	if (!data.empty()) {
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), &data.front(), GL_STATIC_DRAW);
		_count = static_cast<unsigned int>(data.size());
	}
}

int gl::ArrayBuffer::get_count() const
{
	return _count;
}

gl::IndexBuffer::IndexBuffer()
{
	glGenBuffers(1, &_iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboId);
}

gl::IndexBuffer::IndexBuffer(vector<unsigned int>& indices)
{
	glGenBuffers(1, &_iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboId);

	if (!indices.empty()) {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);
		_count = static_cast<unsigned int>(indices.size());
	}
}

gl::IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &_iboId);
}

void gl::IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboId);
}

void gl::IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void gl::IndexBuffer::set_data(vector<unsigned int>& indices)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboId);

	if (!indices.empty()) {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);
		_count = static_cast<unsigned int>(indices.size());
	}
}

int gl::IndexBuffer::get_count() const
{
	return _count;
}

gl::VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_vaoId);
	glBindVertexArray(_vaoId);
}

gl::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &_vaoId);
}

void gl::VertexArray::bind() const
{
	glBindVertexArray(_vaoId);
}

void gl::VertexArray::unbind() const
{
	glBindVertexArray(0);
}

void gl::VertexArray::add_vbo(ArrayBuffer& buffer)
{
	buffer.bind();
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coord));
	glEnableVertexAttribArray(1);
}

void gl::VertexArray::add_ibo(IndexBuffer& buffer)
{
	buffer.bind();
}

