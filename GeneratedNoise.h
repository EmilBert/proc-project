#pragma once
#include <FastNoise/FastNoiseLite.h>
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
	std::pair<int, BiomeType> GetHeight(int x, int z, int maxHeight);

	// Get noise at x y z
	bool GetNoise(int x, int y, int z);

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
};

