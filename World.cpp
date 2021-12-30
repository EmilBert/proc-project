#include "World.h"
#include <FastNoise/FastNoiseLite.hpp>


World::World()
{
	chunks.reserve(9);
	//blocks = std::vector<std::vector<std::vector<bool>>>(3*WIDTH, std::vector<std::vector<bool>>(3*HEIGHT, std::vector<bool>(3*WIDTH, false)));

	for (size_t x = 0; x < 3; x++) {
		for (size_t z = 0; z < 3; z++) {
			chunks.push_back(Chunk( glm::vec3(x,0,z)));
		}
	}
}

World::World(int r) 
{
	range = r;

	chunks.reserve(range * range);
	//blocks = std::vector<std::vector<std::vector<bool>>>(range * WIDTH, std::vector<std::vector<bool>>(range * HEIGHT, std::vector<bool>(range * WIDTH, false)));
	blocksHeightMap = std::vector<std::vector<int>>(range * WIDTH, std::vector<int>(range * WIDTH, 1));

	GenerateHeightMap();

	for (size_t x = 0; x < range; x++) {
		for (size_t z = 0; z < range; z++) {
			chunks.push_back(Chunk(glm::vec3(x, 0, z), blocksHeightMap));
		}
	}
}

void World::GenerateHeightMap()
{
	FastNoiseLite simplexNoise;
	simplexNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

	FastNoiseLite cellularNoise;
	cellularNoise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);

	FastNoiseLite perlinNoise;
	perlinNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

	FastNoiseLite cubicNoise;
	cubicNoise.SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);

	float temp;
	for (int x = 0; x < WIDTH * range; x++)
	{
		for (int z = 0; z < WIDTH * range ; z++)
		{
			// Combine noise into desired effect
			temp	=	simplexNoise.GetNoise((float)x, (float)z) * 2;
			temp	-=	(int)cubicNoise.GetNoise((float)x, (float)z)*0.3;
			temp	+=	perlinNoise.GetNoise((float)x, (float)z);
			temp	+=	cellularNoise.GetNoise((float)x, (float)z);

			temp /= 4;

			//std::cout << temp << std::endl;

			blocksHeightMap[x][z] = (int)(((temp+1)/2 )*HEIGHT);
		}
	}
}

void World::Draw(Shader& shader, Camera& camera)
{
	for (int i = 0; i < chunks.size(); i++)
	{
		chunks[i].Draw(shader, camera);
	}
}
