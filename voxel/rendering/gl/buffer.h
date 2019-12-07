#pragma once
#include <glm/glm.hpp>
#include <vector>

using std::vector;

namespace gl {

struct Vertex {
	Vertex(glm::vec3 pos, glm::vec3 coord);
	Vertex(glm::vec3, glm::vec2 coord);
	Vertex(float x, float y, float z, float u, float v, float layer = 0);

	Vertex(const Vertex&) = default;
	Vertex& operator=(const Vertex&) = default;
	
	glm::vec3 position;
	glm::vec3 tex_coord;
};

class ArrayBuffer {
public:
	ArrayBuffer();
	ArrayBuffer(vector<Vertex>& data);
	~ArrayBuffer();

	void bind() const;
	void unbind() const;
	void set_data(vector<Vertex>& data);

	int get_count() const;

protected:
	unsigned int _vboId = 0;
	unsigned int _count = 0;
};

class IndexBuffer {
public:
	IndexBuffer();
	IndexBuffer(vector<unsigned int>& indices);
	~IndexBuffer();

	void bind() const;
	void unbind() const;
	void set_data(vector<unsigned int>& indices);

	int get_count() const;

protected:
	unsigned int _iboId = 0;
	unsigned int _count = 0;
};

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;

	void add_vbo(ArrayBuffer& buffer);
	void add_ibo(IndexBuffer& buffer);

protected:
	unsigned int _vaoId = 0;
};

}