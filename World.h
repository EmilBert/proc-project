#pragma once
#include "Chunk.h"
#include "Block.h"


class World
{
public:
	std::vector<std::vector<std::vector<Block>>> blocksData;
	std::vector<std::vector<std::vector<bool>>> blocks;
	std::vector<std::vector<int>> blocksHeightMap;
	
	static glm::vec3 sand;
	static glm::vec3 grass;
	static glm::vec3 stone;
	static glm::vec3 snow;

	// Storage of chunks
	std::vector<Chunk> chunks;
	int range;

public:
	World();
	World(int range);

	void GenerateHeightMap();
	void Generate3D();
	void Generate3DBlocks();
	void Draw(Shader& shader, Camera& camera);
};

