#include "World.h"
#include <noise/noise.h>


World::World()
{
	worldHeight = 3 * HEIGHT;
	worldWidth = 3 * WIDTH;

	for (size_t x = 0; x < 3; x++) {
		for (size_t z = 0; z < 3; z++) {
			chunks.push_back(Chunk( glm::vec3(x,0,z)) );
		}
	}
}

World::World(int range) 
{
	worldHeight = range * HEIGHT;
	worldWidth	= range * WIDTH;

	//GenerateHeightMap();

	noise::module::Perlin myModule;
	noise::utils::NoiseMap heightMap;
	noise::utils::NoiseMapBuilderPlane heightMapBuilder;

	heightMapBuilder.SetSourceModule(myModule);
	heightMapBuilder.SetDestNoiseMap(heightMap);

	heightMapBuilder.SetDestSize(worldWidth, worldWidth);
	heightMapBuilder.SetBounds(2.0, 6.0, 1.0, 5.0);
	heightMapBuilder.Build();

	for (size_t x = 0; x < range; x++) 
	for (size_t z = 0; z < range; z++) 
	{
		chunks.push_back(Chunk(glm::vec3(x, 0, z), heightMap));
	}
	
}

void World::GenerateHeightMap()
{
	module::Perlin myModule;
	utils::NoiseMap heightMap;
	utils::NoiseMapBuilderPlane heightMapBuilder;
	
	heightMapBuilder.SetSourceModule(myModule);
	heightMapBuilder.SetDestNoiseMap(heightMap);

	heightMapBuilder.SetDestSize(worldWidth, worldWidth);
	heightMapBuilder.SetBounds(2.0, 6.0, 1.0, 5.0);
	heightMapBuilder.Build();


}

//std::vector<std::vector<std::vector<bool>>> World::GetChunkBools(int world_x, int world_z)
//{
//
//	std::vector<std::vector<std::vector<bool>>> temp;
//
//	for (size_t x = world_x * WIDTH;	x < (world_x + 1) * WIDTH;	x++)
//	for (size_t y = 0;					y < HEIGHT;					y++)
//	for (size_t z = world_z * WIDTH;	z < (world_z + 1)*WIDTH;	z++)
//	{
//		temp.
//	}
//
//
//	return std::vector<std::vector<std::vector<bool>>>();
//}

void World::Draw(Shader& shader, Camera& camera)
{
	for (int i = 0; i < chunks.size(); i++)
	{
		chunks[i].Draw(shader, camera);
	}
}


