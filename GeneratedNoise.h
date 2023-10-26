#pragma once
#include <FastNoise/FastNoiseLite.h>
#include "Block.h"
#include <thread>
#include <string>

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

class GeneratedNoise
{
public:
	// Constructor
	GeneratedNoise();
	GeneratedNoise(int seed);

	// Get noise at x z
	std::pair<int, BiomeType> GetHeightAndBiome(int x, int z);

	// Return a generated chunk
	void GenerateChunkBlocks(int start_x, int start_y, Block blocks[][HEIGHT][WIDTH]);

private:
	// Noise for each biome
	FastNoiseLite simplexNoise;
	FastNoiseLite perlinNoise;
	FastNoiseLite simplexNoise3D;
	FastNoiseLite cubicNoise;
	FastNoiseLite cubicWarp;
	FastNoiseLite cellularNoise;
	FastNoiseLite biomeNoise;
	FastNoiseLite biomeWarp;
	FastNoiseLite perlinMountainsNoise;
	FastNoiseLite cellularMountainsNoise;
	FastNoiseLite perlinMesaNoise;
	FastNoiseLite MountainIceNoise;
	FastNoiseLite caveNoise;

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

};

