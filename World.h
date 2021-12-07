#pragma once
#include "Chunk.h"

class World
{
public:
	// Storage of chunks
	std::vector<Chunk> chunks;
	
	World();
	World(int range);

	void GenerateHeightMap();

	void Draw(Shader& shader, Camera& camera);
};

