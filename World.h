#pragma once
#include "Chunk.h"
#include <vector>

/*
World is a container for the chunks and noise.
*/

class World
{
public:
	
	std::vector<std::vector<std::vector<bool>>> worldBools;
	int worldHeight;
	int worldWidth;

public:
	// Storage of chunks
	std::vector<Chunk> chunks;
	
	// Default constructor (3*3 Chunks)
	World();

	// Create a world with Range*Range Chunks
	World(int range);

	void GenerateHeightMap();

	//std::vector<std::vector<std::vector<bool>>> GetChunkBools(int world_x, int world_z);

	void Draw(Shader& shader, Camera& camera);
};

