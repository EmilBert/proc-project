#pragma once
#include "Chunk.h"
#include "Block.h"
#include "GeneratedNoise.h"
#include <map>
#include <queue>
#include <thread>

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
	std::vector<glm::vec2> relativeIndex;
	std::map<std::pair<int, int>, Chunk*> chunkMap;

	
	bool rendering = false;
	std::thread* renderThread;
	std::queue<Chunk*> renderQueue;
	
	
	GeneratedNoise generatedNoise;
	int range;
	int radius;
	int noise_seed;

	glm::vec2 lastCameraPos = {0, 0};

public:
	World();
	World(int range, int seed);
	void UpdateChunksToRender(glm::vec3 camPos);
	void GenerateChunkMeshes();
	void Draw(Shader& shader, Shader& waterShader, Camera& camera);
};

