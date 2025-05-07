#pragma once
#include <map>
#include <memory>
#include <string>
#include "block.h"

using std::string;
using std::array;
using std::unique_ptr;

template <typename _Kty, typename _Ty> 
using map = std::map<_Kty, _Ty>;

using Database = map<BlockType, array<int, 6>>;

class BlockData {
private:
	static unique_ptr<BlockData> _instance;

public:
	BlockData() = default;

	BlockData(const BlockData&) = delete;
	BlockData(BlockData&&) = delete;
	BlockData& operator=(const BlockData&) = delete;
	BlockData& operator=(BlockData&&) = delete;

	static BlockData& get();

	void set_face_tex(BlockType type, Face face, int layer);
	int get_face_tex(BlockType type, Face face);

protected:
	Database _texture_map;
};