#pragma once
#include <glm/glm.hpp>
#include "chunk.h"
#include <rendering/mesh.h>
#include <memory>

using std::shared_ptr;

class AdjacentBlocks {
public:
	void set(int x, int y, int z);

public:
	glm::vec3 up, down, left, right, front, back;
};

class ChunkGenerator {
public:
	ChunkGenerator() = default;
	virtual ~ChunkGenerator() = default;

	vector<unsigned int> get_indices(vector<gl::Vertex>& vertices);

	shared_ptr<Mesh> build_mesh(shared_ptr<Chunk> chunk);
	vector<gl::Vertex> create_cube(int x, int y, int z, BlockType type, Chunk* chunk);

protected:
	AdjacentBlocks _adjacent;
};