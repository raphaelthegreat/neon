#pragma once
#include <rendering/gl/buffer.h>

extern vector<gl::Vertex> front;
extern vector<gl::Vertex> right;
extern vector<gl::Vertex> back;
extern vector<gl::Vertex> left;
extern vector<gl::Vertex> bottom;
extern vector<gl::Vertex> top;
extern vector<unsigned int> quad_indices;

class FaceData {
public:
	FaceData(vector<gl::Vertex>& vertices);

	void set_tex_layer(int layer);
	vector<gl::Vertex> get_vertices();
	
	void add_offset_to_vertices(float offsetx, float offsety, float offsetz);

protected:
	vector<gl::Vertex> _vertices;
};