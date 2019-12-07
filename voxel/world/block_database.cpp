#include "block_database.h"

unique_ptr<BlockData> BlockData::_instance;

BlockData& BlockData::get()
{
	if (_instance == nullptr) {
		_instance = std::make_unique<BlockData>();
	}

	return *_instance;
}

void BlockData::set_face_tex(BlockType type, Face face, int layer)
{
	_texture_map[type][(int)face] = layer;
}

int BlockData::get_face_tex(BlockType type, Face face)
{
	return _texture_map[type][(int)face];
}
