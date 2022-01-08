#pragma once
#include "Chunk.h"
#include "Block.h"

enum BiomeType
{
	hills = 0,
	desert = 1,
	mesa = 2,
	glacier = 3,
	forest = 4,
	mountains = 5,
	ocean = 6
};

class World
{
public:
	std::vector<std::vector<std::vector<Block>>> blocksData;
	std::vector<std::vector<std::vector<bool>>> blocks;
	std::vector<std::vector<std::pair<int, BiomeType>>> blocksHeightMap;
	
	static glm::vec3 sand;
	static glm::vec3 moss;
	static glm::vec3 grass;
	static glm::vec3 stone;
	static glm::vec3 ice;
	static glm::vec3 snow;
	static glm::vec3 clay;
	static glm::vec3 water;



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

