#pragma once

#include "Block.h"

const int WIDTH = 16;
const int HEIGHT = 64;

struct BlockData {
	bool solid;
	glm::vec3 position;
};


class Chunk
{
public:

	std::vector<BlockData> blocks;
	std::vector<Block> blockRenderer;

	Chunk();
	void Draw(Shader& shader, Camera& camera);
};

