#pragma once
#include "Chunk.h"


class World
{
public:
	// Storage of chunks

	std::vector<std::vector<std::vector<bool>>> blocks;
	std::vector<std::vector<int>> blocksHeightMap;
	std::vector<Chunk> chunks;
	int range;

public:
	World();
	World(int range);

	void GenerateHeightMap();
	void Draw(Shader& shader, Camera& camera);
};

