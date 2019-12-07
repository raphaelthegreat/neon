#pragma once
#include "block_database.h"
#include "chunk_generator.h"
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <iterator>

#define ASYNC_NUM_CHUNKS 2

class CmpVec {
public:
	bool operator()(const glm::vec2& r, const glm::vec2& l) const {
		if (r.x == l.x)
			return r.y > l.y;
		else
			return r.x > l.x;
	}
};

class Renderer;

class ChunkManager {
public:
	ChunkManager();

	void add_chunk(const glm::vec2& pos);
	void delete_chunk(const glm::vec2& pos);
	shared_ptr<Chunk> get_chunk(const glm::vec2& pos);
	
	void update(const glm::vec3& plpos);
	void render(Renderer* renderer);

public:
	unique_ptr<ChunkGenerator> _generator;
	std::unordered_map<glm::vec2, shared_ptr<Chunk>> _chunks;

	std::vector<glm::vec2> _load;
	std::vector<glm::vec2> _remove;

	int _chunks_loaded = 0;
	AdjacentChunks _adjacent;
};