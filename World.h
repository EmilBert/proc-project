#pragma once
#include "Chunk.h"
#include "Block.h"


class World
{
public:
	std::vector<std::vector<std::vector<Block>>> blocksData;
	std::vector<std::vector<std::vector<bool>>> blocks;
	std::vector<std::vector<int>> blocksHeightMap;
	
	// Storage of chunks
	std::vector<Chunk> chunks;
	int range;

public:
	World();
	World(int range);

	void GenerateHeightMap();
	void Generate3D();
	void Draw(Shader& shader, Camera& camera);
};

