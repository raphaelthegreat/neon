#include "chunk_manager.h"
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <algorithm>
#include <rendering/renderer.h>

using namespace std;

ChunkManager::ChunkManager()
{
	_generator = std::make_unique<ChunkGenerator>();
}

void ChunkManager::add_chunk(const glm::vec2& pos)
{
	_chunks[pos] = std::make_shared<Chunk>(this, pos);
}

void ChunkManager::delete_chunk(const glm::vec2& pos)
{
	if (_chunks.count(pos)) {
		_chunks.erase(pos);
	}
}

shared_ptr<Chunk> ChunkManager::get_chunk(const glm::vec2& pos)
{
	if (_chunks.count(pos)) {
		return _chunks[pos];
	}
	else {
		return nullptr;
	}
}

void ChunkManager::update(const glm::vec3& playerpos)
{
	auto plpos = glm::vec2(playerpos.x, playerpos.z);
	auto chunkpos = glm::floor(plpos / glm::vec2(CHUNK_SIZE * 2));

	auto px = std::make_pair(chunkpos.x - VIEW_DIST, chunkpos.x + VIEW_DIST);
	auto py = std::make_pair(chunkpos.y - VIEW_DIST, chunkpos.y + VIEW_DIST);
	
	// Chunks to load
	for (int x = px.first; x < px.second; x++) {
		for (int y = py.first; y < py.second; y++) {
			auto pos = glm::vec2(x, y);
			
			if (!_chunks.count(pos)) {
				_load.push_back(pos);
			}
		}
	}

	// Chunks to unload
	for (auto& c : _chunks) {
		auto chunk = c.second;
		auto pos = chunk->get_location();

		if (pos.x < px.first || pos.x > px.second || pos.y < py.first || pos.y > py.second) {
			delete_chunk(c.first);
		}
	}

	if (!_load.empty()) {
		for (auto& pos : _load) {
			add_chunk(pos);

			auto chunk = get_chunk(pos);
			auto mesh = _generator->build_mesh(chunk);
			chunk->set_mesh(mesh);
			chunk->set_load_state(false);

			_chunks_loaded++;
		}
	}
	
	_load.clear();
	_chunks_loaded = 0;

	
}

void ChunkManager::render(Renderer* renderer)
{
	for (auto& c : _chunks) {
		auto chunk = c.second;
		if (!chunk->get_load_state() && !chunk->get_unload_state()) {
			auto mesh = chunk->get_mesh();
			auto pos = chunk->get_location();

			auto pos3d = glm::vec3(pos.x * 32, 0, pos.y * 32);

			//std::cout << glm::to_string(pos) << "\n";

			renderer->set_translation(pos3d);
			renderer->draw(mesh);
		}
	}

	//std::cout << chunks.size() << "\n";
}
