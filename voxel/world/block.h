#pragma once
#include <array>

enum BlockType : uint8_t {
	Block_Grass
};

enum Face : uint8_t {
	Top,
	Bottom,
	Left,
	Right,
	Front,
	Back
};

class Block {
public:
	Block() = default;
	Block(BlockType block) : _block(block) {}

	bool is_active() { return _active; }
	void set_ative(bool active) { _active = active; }
	BlockType get_id() { return _block; }

protected:
	bool _active = true;
	BlockType _block = Block_Grass;
};