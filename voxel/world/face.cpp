#include "face.h"

vector<gl::Vertex> front = {
	{-1.0f, -1.0f, 1.0f,	0.0f, 0.0f},
	{ 1.0f, -1.0f, 1.0f,	1.0f, 0.0f},
	{-1.0f,  1.0f, 1.0f,	0.0f, 1.0f},
	{ 1.0f,  1.0f, 1.0f,	1.0f, 1.0f}
};

vector<gl::Vertex> right = {
	{ 1.0f, -1.0f,  1.0f,	0.0f, 0.0f},
	{ 1.0f, -1.0f, -1.0f,	1.0f, 0.0f},
	{ 1.0f,  1.0f,  1.0f,	0.0f, 1.0f},
	{ 1.0f,  1.0f, -1.0f,	1.0f, 1.0f}
};

vector<gl::Vertex> back = {
	{ 1.0f, -1.0f, -1.0f,	0.0f, 0.0f},
	{-1.0f, -1.0f, -1.0f,	1.0f, 0.0f},
	{ 1.0f,  1.0f, -1.0f,	0.0f, 1.0f},
	{-1.0f,  1.0f, -1.0f,	1.0f, 1.0f}
};

vector<gl::Vertex> left = {
	{-1.0f, -1.0f, -1.0f,	0.0f, 0.0f},
	{-1.0f, -1.0f,  1.0f,	1.0f, 0.0f},
	{-1.0f,  1.0f, -1.0f,	0.0f, 1.0f},
	{-1.0f,  1.0f,  1.0f,	1.0f, 1.0f}
};

vector<gl::Vertex> bottom = {
	{-1.0f, -1.0f, -1.0f,	0.0f, 1.0f},
	{ 1.0f, -1.0f, -1.0f,	0.0f, 0.0f},
	{-1.0f, -1.0f,  1.0f,	1.0f, 1.0f},
	{ 1.0f, -1.0f,  1.0f,	1.0f, 0.0f}
};

vector<gl::Vertex> top = {
	{-1.0f, 1.0f,  1.0f,	0.0f, 0.0f},
	{ 1.0f, 1.0f,  1.0f,	1.0f, 0.0f},
	{-1.0f, 1.0f, -1.0f,	0.0f, 1.0f},
	{ 1.0f, 1.0f, -1.0f,	1.0f, 1.0f}
};

std::vector<unsigned int> quad_indices = {
	0, 1, 3,
	0, 3, 2
};

FaceData::FaceData(vector<gl::Vertex>& vertices)
{
	_vertices = vertices;
}

void FaceData::set_tex_layer(int layer)
{
	for (auto& v : _vertices) {
		auto coords = v.tex_coord;

		glm::vec3 new_coord = glm::vec3(coords.x, coords.y, layer);
		v.tex_coord = new_coord;
	}
}

vector<gl::Vertex> FaceData::get_vertices()
{
	return _vertices;
}

void FaceData::add_offset_to_vertices(float offsetx, float offsety, float offsetz)
{
	for (auto& v : _vertices) {
		auto vertex = v.position;

		vertex += glm::vec3(offsetx, offsety, offsetz);
		v.position = vertex;
	}
}
