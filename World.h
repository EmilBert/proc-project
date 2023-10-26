#pragma once
#include "Chunk.h"
#include "Block.h"
#include "GeneratedNoise.h"

class World
{
public:
	static glm::vec3 sand;
	static glm::vec3 moss;
	static glm::vec3 grass;
	static glm::vec3 stone;
	static glm::vec3 ice;
	static glm::vec3 snow;
	static glm::vec3 clay;
	static glm::vec3 claydark;
	static glm::vec3 water;
	static glm::vec3 dirt;

	// Storage of chunks
	std::vector<std::vector<Chunk>> chunksToRender;
	GeneratedNoise generatedNoise;
	int range;
	int noise_seed;

	glm::vec2 cameraChunkCoord = {0, 0};

public:
	World();
	World(int range, int seed);
	void GenerateChunkMesh(int x, int z, Chunk& chunk);
	void UpdateChunksToRender(glm::vec3 camPos);
	void Draw(Shader& shader, Shader& waterShader, Camera& camera);
};

