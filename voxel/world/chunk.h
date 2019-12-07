#pragma once
#include <world/block.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include <memory>
#include <rendering/mesh.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

using std::shared_ptr;

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 128
#define CHUNK_VOLUME CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT

#define VIEW_DIST 10

class ChunkManager;
class Chunk {
public:
	Chunk() = default;
	Chunk(ChunkManager* manager, const glm::vec2& location);

	void set_block(int x, int y, int z, Block block);
	Block& get_block(int x, int y, int z) noexcept;
	Block& get_block(const glm::vec3& pos) noexcept;

	const glm::vec2& get_location() const;
	
	bool get_load_state() { return _must_load; }
	void set_load_state(bool loaded) { _must_load = loaded; }

	bool get_unload_state() { return _must_unload; }
	void set_unload_state(bool state) { _must_unload = state; }

	int get_height_at(int x, int z) { return _heights[glm::vec2(x, z)]; }

	void set_mesh(shared_ptr<Mesh> mesh) { _chunk_mesh = mesh; }
	shared_ptr<Mesh> get_mesh() { return _chunk_mesh; }

	auto get_manager() { return _manager; }

	bool out_of_bound(int x, int y, int z);
	bool out_of_bound(const glm::vec3& pos);

protected:
	std::vector<std::vector<std::vector<Block>>> _blocks;
	ChunkManager* _manager;

	std::unordered_map<glm::vec2, int> _heights;

	shared_ptr<Mesh> _chunk_mesh;

	glm::vec2 _location;

	bool _must_load = true;
	bool _must_unload = false;
};

class AdjacentChunks {
public:
	void set(int x, int y)
	{
		left = glm::vec2(x - 1, y);
		right = glm::vec2(x + 1, y);
		front = glm::vec2(x, y + 1);
		back = glm::vec2(x, y - 1);
	}
	void update(const glm::vec2& plpos)
	{
		auto xdiff = left.x * CHUNK_SIZE - plpos.x;
		auto ydiff = left.y * CHUNK_SIZE - plpos.y;

		ldist = (int)round(sqrt(pow(xdiff, 2) + pow(ydiff, 2)) / CHUNK_SIZE);

		xdiff = right.x * CHUNK_SIZE - plpos.x;
		ydiff = right.y * CHUNK_SIZE - plpos.y;

		rdist = (int)round(sqrt(pow(xdiff, 2) + pow(ydiff, 2)) / CHUNK_SIZE);

		xdiff = front.x * CHUNK_SIZE - plpos.x;
		ydiff = front.y * CHUNK_SIZE - plpos.y;

		fdist = (int)round(sqrt(pow(xdiff, 2) + pow(ydiff, 2)) / CHUNK_SIZE);

		xdiff = back.x * CHUNK_SIZE - plpos.x;
		ydiff = back.y * CHUNK_SIZE - plpos.y;

		bdist = (int)round(sqrt(pow(xdiff, 2) + pow(ydiff, 2)) / CHUNK_SIZE);
	}

	glm::vec2 left, right, front, back;
	int ldist, rdist, fdist, bdist;
};