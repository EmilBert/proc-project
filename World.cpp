#include "World.h"
#include <FastNoise/FastNoiseLite.h>
#include <iostream>
#include <thread>
#include <atomic>

glm::vec3 World::sand	= glm::vec3(0.76, 0.69, 0.5);
glm::vec3 World::grass	= glm::vec3(0.0, 0.40f, 0.09);
glm::vec3 World::moss	= glm::vec3(0.04, 0.32f, 0.07);
glm::vec3 World::stone	= glm::vec3(0.392, 0.392, 0.392);
glm::vec3 World::snow	= glm::vec3(0.8, 0.8, 1.0);
glm::vec3 World::ice	= glm::vec3(0.4, 0.6, 1.0);
glm::vec3 World::clay	= glm::vec3(0.70, 0.40, 0.15);
glm::vec3 World::claydark = glm::vec3(0.50, 0.25, 0.10);
glm::vec3 World::water	= glm::vec3(0.2, 0.2, 1.0);
glm::vec3 World::dirt	= glm::vec3(0.3, 0.2, 0.2);

World::World(){}

World::World(int r, int seed) : radius(r), range(r * 2 + 1), noise_seed(seed)
{
	generatedNoise = GeneratedNoise(seed);

	for (int x = -radius; x < radius; x++)
	{
		for (int z = -radius; z < radius; z++)
		{
			std::cout << x << " " << z << "\n";
			relativeIndex.push_back(glm::vec2(x, z));
		}
	}
}
			//chunkMap.insert(std::make_pair(std::make_pair(x,z), new Chunk(glm::vec2(x, z), generatedNoise)));

/*
void World::Generate3DBlocks()
{
	FastNoiseLite MountainIceNoise;
	MountainIceNoise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
	MountainIceNoise.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Hybrid);
	MountainIceNoise.SetCellularReturnType(FastNoiseLite::CellularReturnType_CellValue);
	MountainIceNoise.SetFrequency(0.1);

	FastNoiseLite caveNoise;
	caveNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
	caveNoise.SetFractalType(FastNoiseLite::FractalType_Ridged);
	caveNoise.SetFractalOctaves(2);
	caveNoise.SetSeed(noise_seed);
	caveNoise.SetFrequency(0.010);


	for (size_t x = 0; x < WIDTH * range; x++)
	for (size_t z = 0; z < WIDTH * range; z++)
	{
		glm::vec3 blockColor = stone;
		size_t y = 0;
		
		for (; y < blocksHeightMap[x][z].first; y++)
		{
			if (y > 5 &&  caveNoise.GetNoise((float)x, (float)y, (float)z) > 0.9) continue;
			
			blocksData[x][y][z]  = Block(true, glm::vec3(x, y, z), stone);
		}

		std::vector<Block>;

		Decide biome & set settings
		switch (blocksHeightMap[x][z].second)
		{
		case hills:
			blockColor = grass;
			blocksData[x][y - 1][z].color = blockColor;
			blocksData[x][y - 2][z].color = dirt;
			blocksData[x][y - 3][z].color = dirt;
			blocksData[x][y - 4][z].color = dirt;
			break;
		case desert:
			blockColor = sand;
			for (int k = y; k > y - 10; k--) {
				blocksData[x][k][z].color = blockColor;
			}
			if ( (float)rand()/RAND_MAX < 0.001 && y > 20) {
				blocksData[x][y][z]		= Block(true, glm::vec3(x, y ,z), grass);
				blocksData[x][y+1][z]	= Block(true, glm::vec3(x, y + 1, z), grass);
				blocksData[x][y+2][z]	= Block(true, glm::vec3(x, y + 2, z), grass);
			}
			break;

		case mesa:
			blockColor = clay;
			for (int k = y; k > 20; k--) {
				if ((float)rand() / RAND_MAX < 0.9 && y > 20) {
					if (k < 65 && k > 62) {
						blocksData[x][k][z].color = dirt;
						continue;
					}
					if (k < 61 && k > 58) {
						blocksData[x][k][z].color = claydark;
						continue;
					}
				}
				blocksData[x][k][z].color = blockColor;
			}
			break;

		case glacier:
			blockColor = ice;
			break;
		case forest:
			blockColor = moss;
			blocksData[x][y - 1][z].color = blockColor;
			blocksData[x][y - 2][z].color = dirt;
			blocksData[x][y - 3][z].color = dirt;
			blocksData[x][y - 4][z].color = dirt;
			
			if ((float)rand() / RAND_MAX < 0.005 && y > 20) {
				GrowTree(glm::vec3(x, y, z));
			}

			break;

		case mountains:
			blockColor = snow;
			if (MountainIceNoise.GetNoise((float)x, (float)z) > 0.5 && y > 80) blockColor = ice;
			blocksData[x][y - 1][z].color = blockColor;
			blocksData[x][y - 2][z].color = dirt;
			blocksData[x][y - 3][z].color = stone;
			blocksData[x][y - 4][z].color = stone;
			break;
		case ocean:
			blockColor = sand;
			blocksData[x][y - 1][z].color = blockColor;
			break;

		default:
			blockColor = stone;
			break;
		}

		 Add ocean
		for (; y < 20; y++)
		{
			blocksData[x][y][z] = Block(false, glm::vec3(x, y, z), water);
			blocksData[x][y][z].isTransparent = true;
		}
	}
}
*/
/*oid World::InsertBlock(Block in)
{
	int x = in.position.x;
	int y = in.position.y;
	int z = in.position.z;
	blocksData[x][y][z] = in;
}*/
//void World::GrowTree(glm::vec3 pos) {
//	
//	int x = pos.x;
//	int y = pos.y;
//	int z = pos.z;
//	
//	if (x < 1 || x > WIDTH*range - 2 || z < 1 || z > WIDTH * range - 2) return;
//
//	for (int y_ = y; y_ < y + 5; y_++)
//		blocksData[x][y_][z] = Block(true, glm::vec3(x,y_,z), dirt);
//	
//
//	for (int x_ = x-1; x_ < x + 2; x_++)
//	for (int z_ = z-1; z_ < z + 2; z_++)
//	for (int y_ = y+3; y_ < y + 5; y_++)
//		blocksData[x_][y_][z_] = Block(true, glm::vec3(x_, y_, z_), grass);
//	
//		
//	blocksData[x-1][y+5][z]		= Block(true,	glm::vec3(x-1, y+5, z),		grass);
//	blocksData[x][y + 5][z-1]	= Block(true,	glm::vec3(x, y + 5, z-1),	grass);
//	blocksData[x+1][y + 5][z]	= Block(true,	glm::vec3(x+1, y + 5, z),	grass);
//	blocksData[x][y + 5][z+1]	= Block(true,	glm::vec3(x, y + 5, z+1),	grass);
//	blocksData[x][y + 5][z]		= Block(true,	glm::vec3(x, y + 5, z),		grass);
//}

//void World::GenerateChunkMesh(int x, int z, Chunk& chunk)
//{
//	Chunk* left		 = (x == 0)			? nullptr : &chunksToRender[x - 1][z];
//	Chunk* right	 = (x == range-1)	? nullptr : &chunksToRender[x + 1][z];
//	Chunk* behind	 = (z == 0)			? nullptr : &chunksToRender[x][z - 1];
//	Chunk* infront   = (z == range-1)	? nullptr : &chunksToRender[x][z + 1];
//
//	chunk.GenerateMesh(left, right, infront, behind);
//}


// The chunkMap should be updated to contain chunks within the radius of the camera
// If they are outside of that radius they should be removed.
void World::UpdateChunksToRender(glm::vec3 camPos)
{
	glm::vec2 cameraPos((int)camPos.x, (int)camPos.z);
	if (lastCameraPos == cameraPos) return;
	std::pair<int, int> cameraPair(camPos.x, camPos.z);
	lastCameraPos = cameraPos;

	std::map<std::pair<int, int>, Chunk*> newChunkMap;

	// Check what chunks to add
	for (glm::vec2 relationToCam : relativeIndex)
	{
		glm::vec2 p = lastCameraPos + relationToCam;

		std::pair<int, int> pp = std::make_pair(p.x, p.y);

		auto it = chunkMap.find(pp);

		// Add existing to new map
		if (it != chunkMap.end())
		{
			newChunkMap.insert(make_pair(it->first, it->second));
		}
		// Add new chunk to map
		else
		{
			Chunk* newChunk = new Chunk(p, generatedNoise);
			newChunkMap.insert(std::make_pair(pp, newChunk));
			renderQueue.push(newChunk);
		}
	}
	chunkMap.clear();
	chunkMap = newChunkMap;
}

void World::GenerateChunkMeshes()
{
	if (renderQueue.empty()) return;
	renderQueue.front()->GenerateMesh();
	renderQueue.pop();
}

void World::Draw(Shader& shader, Shader& waterShader, Camera& camera)
{
	//std::thread th = std::thread(&World::UpdateChunksToRender, this, camera.Position);

	UpdateChunksToRender(camera.Position);
	GenerateChunkMeshes();

	for (auto it = chunkMap.begin(); it != chunkMap.end(); it++)
	{
		if(!it->second->regenMesh)
		{
			it->second->Draw(shader, camera);	
		}
	}
}