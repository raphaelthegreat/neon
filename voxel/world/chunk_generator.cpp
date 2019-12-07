#include "chunk_generator.h"
#include "block_database.h"
#include "face.h"
#include "chunk_manager.h"
#include <iostream>

void AdjacentBlocks::set(int x, int y, int z)
{
	up =    glm::vec3(x,     y + 1, z);
	down =  glm::vec3(x,     y - 1, z);
	left =  glm::vec3(x - 1, y,     z);
	right = glm::vec3(x + 1, y,     z);
	front = glm::vec3(x,     y,     z + 1);
	back =  glm::vec3(x,     y,     z - 1);
}

vector<unsigned int> ChunkGenerator::get_indices(vector<gl::Vertex>& vertices)
{
	std::vector<unsigned int> indices;
	
	for (int i = 0; i < vertices.size(); i += 4) {
		auto copy = quad_indices;

		for (auto& index : copy) {
			index += i;
		}

		indices.insert(indices.end(), copy.begin(), copy.end());
	}

	return indices;
}

shared_ptr<Mesh> ChunkGenerator::build_mesh(shared_ptr<Chunk> chunk)
{
	vector<gl::Vertex> chunk_data;
	
	for (int x = 0; x < CHUNK_SIZE; x++) {
	for (int y = 0; y < CHUNK_HEIGHT; y++) {
	for (int z = 0; z < CHUNK_SIZE; z++) {
		auto block = chunk->get_block(x, y, z);
		
		if (!block.is_active())
			continue;
				
		auto vertices = this->create_cube(x, y, z, block.get_id(), chunk.get());
		chunk_data.insert(chunk_data.end(), vertices.begin(), vertices.end());
	} } }

	auto indices = this->get_indices(chunk_data);

	shared_ptr<Mesh> chunk_mesh = std::make_shared<Mesh>(chunk_data, indices);
	return chunk_mesh;
}

vector<gl::Vertex> ChunkGenerator::create_cube(int _x, int _y, int _z, BlockType type, Chunk* chunk)
{
	auto& database = BlockData::get();

	_adjacent.set(_x, _y, _z);

	vector<gl::Vertex> block_data;
	block_data.reserve(24);
	
	float x = _x * 2.00001f;
	float y = _y * 2.00001f;
	float z = _z * 2.00001f;

	auto pos = chunk->get_location();

	// Top face
	if (chunk->out_of_bound(_adjacent.up)) {
		auto top_face = FaceData(top);
		top_face.set_tex_layer(database.get_face_tex(type, Top));
		top_face.add_offset_to_vertices(x, y, z);
		auto top_data = top_face.get_vertices();

		block_data.insert(block_data.end(), top_data.begin(), top_data.end());
	}
	else {
		if (!chunk->get_block(_adjacent.up).is_active()) {
			// Top face
			auto top_face = FaceData(top);
			top_face.set_tex_layer(database.get_face_tex(type, Top));
			top_face.add_offset_to_vertices(x, y, z);
			auto top_data = top_face.get_vertices();

			block_data.insert(block_data.end(), top_data.begin(), top_data.end());
		}
	}

	// bottom face
	if (chunk->out_of_bound(_adjacent.down)) {
		auto bottom_face = FaceData(bottom);
		bottom_face.set_tex_layer(database.get_face_tex(type, Bottom));
		bottom_face.add_offset_to_vertices(x, y, z);
		auto bottom_data = bottom_face.get_vertices();

		block_data.insert(block_data.end(), bottom_data.begin(), bottom_data.end());
	}
	else {
		if (!chunk->get_block(_adjacent.down).is_active()) {
			// bottom face
			auto bottom_face = FaceData(bottom);
			bottom_face.set_tex_layer(database.get_face_tex(type, Bottom));
			bottom_face.add_offset_to_vertices(x, y, z);
			auto bottom_data = bottom_face.get_vertices();

			block_data.insert(block_data.end(), bottom_data.begin(), bottom_data.end());
		}
	}

	// right face
	if (chunk->out_of_bound(_adjacent.right)) {
		auto right_face = FaceData(right);
		right_face.set_tex_layer(database.get_face_tex(type, Right));
		right_face.add_offset_to_vertices(x, y, z);
		auto right_data = right_face.get_vertices();

		block_data.insert(block_data.end(), right_data.begin(), right_data.end());
	}
	else {
		if (!chunk->get_block(_adjacent.right).is_active()) {
			auto right_face = FaceData(right);
			right_face.set_tex_layer(database.get_face_tex(type, Right));
			right_face.add_offset_to_vertices(x, y, z);
			auto right_data = right_face.get_vertices();

			block_data.insert(block_data.end(), right_data.begin(), right_data.end());
		}
	}

	if (chunk->out_of_bound(_adjacent.left)) {
		// left face
		auto left_face = FaceData(left);
		left_face.set_tex_layer(database.get_face_tex(type, Left));
		left_face.add_offset_to_vertices(x, y, z);
		auto left_data = left_face.get_vertices();

		block_data.insert(block_data.end(), left_data.begin(), left_data.end());
	}
	else {
		if (!chunk->get_block(_adjacent.left).is_active()) {
			// left face
			
			auto left_face = FaceData(left);
			left_face.set_tex_layer(database.get_face_tex(type, Left));
			left_face.add_offset_to_vertices(x, y, z);
			auto left_data = left_face.get_vertices();

			block_data.insert(block_data.end(), left_data.begin(), left_data.end());
		}
	}

	if (chunk->out_of_bound(_adjacent.front)) {
		// front face
		auto front_face = FaceData(front);
		front_face.set_tex_layer(database.get_face_tex(type, Front));
		front_face.add_offset_to_vertices(x, y, z);
		auto front_data = front_face.get_vertices();

		block_data.insert(block_data.end(), front_data.begin(), front_data.end());
	}
	else {
		if (!chunk->get_block(_adjacent.front).is_active()) {
			// front face
			auto front_face = FaceData(front);
			front_face.set_tex_layer(database.get_face_tex(type, Front));
			front_face.add_offset_to_vertices(x, y, z);
			auto front_data = front_face.get_vertices();

			block_data.insert(block_data.end(), front_data.begin(), front_data.end());
		}
	}

	if (chunk->out_of_bound(_adjacent.back)) {

		// back face
		auto back_face = FaceData(back);
		back_face.set_tex_layer(database.get_face_tex(type, Back));
		back_face.add_offset_to_vertices(x, y, z);
		auto back_data = back_face.get_vertices();

		block_data.insert(block_data.end(), back_data.begin(), back_data.end());
	}
	else {
		if (!chunk->get_block(_adjacent.back).is_active()) {
			// back face
			auto back_face = FaceData(back);
			back_face.set_tex_layer(database.get_face_tex(type, Back));
			back_face.add_offset_to_vertices(x, y, z);
			auto back_data = back_face.get_vertices();

			block_data.insert(block_data.end(), back_data.begin(), back_data.end());
		}
	}

	return block_data;
}
