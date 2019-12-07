#include "chunk.h"
#include "chunk_manager.h"
#include <FastNoise.h>
#include <iostream>

Chunk::Chunk(ChunkManager* manager, const glm::vec2& pos)
{
	_manager = manager;
	_location = pos;

	FastNoise myNoise;
	myNoise.SetNoiseType(FastNoise::Simplex);

	for (int x = 0; x < CHUNK_SIZE; x++) {
		_blocks.push_back(std::vector<std::vector<Block>>());
		for (int z = 0; z < CHUNK_SIZE; z++) {
			_blocks[x].push_back(std::vector<Block>());
			
			float posx = x + pos.x * CHUNK_SIZE;
			float posy = z + pos.y * CHUNK_SIZE;
			
			float limit = std::abs(myNoise.GetNoise(posx, posy));
			limit *= CHUNK_HEIGHT - 100;
			_heights[glm::vec2(x, z)] = limit;

			for (int y = 0; y < CHUNK_HEIGHT; y++) {
				_blocks[x][z].push_back(Block());

				if (y > limit) {
					get_block(x, y, z).set_ative(false);
				}
			}
		}
	}
}

void Chunk::set_block(int x, int y, int z, Block block)
{
	_blocks[x][z][y] = block;
}

Block& Chunk::get_block(int x, int y, int z) noexcept
{
	return _blocks[x][z][y];
}

Block& Chunk::get_block(const glm::vec3& pos) noexcept
{
	int x = static_cast<int>(pos.x);
	int y = static_cast<int>(pos.y);
	int z = static_cast<int>(pos.z);
	
	return _blocks[x][z][y];
}

const glm::vec2& Chunk::get_location() const
{
	return _location;
}

bool Chunk::out_of_bound(int x, int y, int z)
{
	bool result = false;
	
	result |= x >= CHUNK_SIZE || x < 0;
	result |= y >= CHUNK_HEIGHT || y < 0;
	result |= z >= CHUNK_SIZE || z < 0;
	
	return result;
}

bool Chunk::out_of_bound(const glm::vec3& pos)
{
	int x = static_cast<int>(pos.x);
	int y = static_cast<int>(pos.y);
	int z = static_cast<int>(pos.z);

	return out_of_bound(x, y, z);
}
