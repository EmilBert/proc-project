#include "World.h"
#include <FastNoise/FastNoiseLite.hpp>

glm::vec3 World::sand	= glm::vec3(0.76f, 0.69f, 0.5f);
glm::vec3 World::grass	= glm::vec3(0.0f, 0.60f, 0.09f);
glm::vec3 World::stone	= glm::vec3(0.392f, 0.392, 0.392);
glm::vec3 World::snow	= glm::vec3(0.8f, 0.8, 1.0f);


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
	//blocksHeightMap = std::vector<std::vector<int>>(range * WIDTH, std::vector<int>(range * WIDTH, 1));
	//blocks = std::vector<std::vector<std::vector<bool>>>(range * WIDTH, std::vector<std::vector<bool>>(HEIGHT, std::vector<bool>(range*WIDTH, false)));
	blocksData = std::vector<std::vector<std::vector<Block>>>(range * WIDTH, std::vector<std::vector<Block>>(HEIGHT, std::vector<Block>(range * WIDTH, Block())));
	
	Generate3DBlocks();

	for (size_t x = 0; x < range; x++) {
		for (size_t z = 0; z < range; z++) {
			chunks.push_back(Chunk(glm::vec3(x, 0, z), blocksData));
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

			blocksHeightMap[x][z] = (int)(((temp+1)/2 )*HEIGHT);
		}
	}
}

void World::Generate3D()
{
	FastNoiseLite simplexNoise;
	simplexNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);

	//FastNoiseLite perlinNoise;
	//perlinNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

	//FastNoiseLite valueNoise;
	//valueNoise.SetNoiseType(FastNoiseLite::NoiseType_Value);

	FastNoiseLite simplexNoise3D;
	simplexNoise3D.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	simplexNoise3D.SetFrequency(0.01);

	FastNoiseLite cubicNoise;
	cubicNoise.SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);
	


	FastNoiseLite cellularNoise;
	cellularNoise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);

	float temp;
	for (int x = 0; x < WIDTH * range; x++)
		for (int z = 0; z < WIDTH * range; z++)
		{
			// Generate Height
			float height = (cubicNoise.GetNoise((float)x, (float)z) + 1) / 3;
			float simplex = (simplexNoise.GetNoise((float)x, (float)z) + 1) / 2;


			if (simplex > height) {
				height = simplex;
			}

			height += (cellularNoise.GetNoise((float)x, (float)z) + 1) / 2;

			int finalHeight = HEIGHT * (height / 2 + 0.1);

			for (int y = 0; y < HEIGHT; y++)
			{
				// Only generate for height
				if (y > finalHeight) {
					blocks[x][y][z] = false;
					break;
				}

				// Combine noise into desired effect
				temp = simplexNoise3D.GetNoise((float)x, float(y), (float)z);
				bool result = false;
				if (temp < 0.8) result = true;
				blocks[x][y][z] = result;
			}
		}
}

void World::Generate3DBlocks()
{
	FastNoiseLite simplexNoise;
	simplexNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
	simplexNoise.SetFrequency(0.05);

	FastNoiseLite perlinNoise;
	perlinNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	perlinNoise.SetFrequency(0.05);

	FastNoiseLite valueNoise;
	valueNoise.SetNoiseType(FastNoiseLite::NoiseType_Value);
	valueNoise.SetFrequency(0.015);
	simplexNoise.SetFractalOctaves(8);
	valueNoise.SetDomainWarpAmp(50);
	valueNoise.SetFractalGain(20);
	valueNoise.SetSeed(1337);

	FastNoiseLite simplexNoise3D;
	simplexNoise3D.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	simplexNoise3D.SetFrequency(0.01);

	FastNoiseLite cubicNoise;
	cubicNoise.SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);

	FastNoiseLite cellularNoise;
	cellularNoise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);

	for (size_t x = 0; x < WIDTH * range; x++)
	for (size_t z = 0; z < WIDTH * range; z++)
	{
		//Height creation
		float cubic		= (cubicNoise.GetNoise(		(float)x,	(float)z) + 1) / 4;
		float simplex	= (simplexNoise.GetNoise(	(float)x,	(float)z) + 1) / 2;
		float value		= (valueNoise.GetNoise((float)x, (float)z) + 1) / 2;
		float cellular	= (cellularNoise.GetNoise(	(float)x,	(float)z) + 1) / 2;
		//float simplex	= (simplexNoise.GetNoise(	(float)x,	(float)z) + 1) / 4;

		size_t y = 0;
		//Add stone
		for (; y < cubic*0.2*HEIGHT; y++) {
			blocksData[x][y][z].isSolid		= true;
			blocksData[x][y][z].color		= stone;
			blocksData[x][y][z].position	= glm::vec3(x, y, z);
		}
		
		// Add hills
		for (; y < (value*0.8) *HEIGHT-1; y++) {
			blocksData[x][y][z].isSolid = true;
			blocksData[x][y][z].color = stone;
			blocksData[x][y][z].position = glm::vec3(x, y, z);
		}

		// Add Beach
		for (size_t y_beach = y; y_beach < y + (cellular * 0.1) * HEIGHT && y < HEIGHT*0.2; y_beach++) {
			blocksData[x][y_beach][z].isSolid = true;
			blocksData[x][y_beach][z].color = sand;
			blocksData[x][y_beach][z].position = glm::vec3(x, y_beach, z);
		}

		// Add Grass
		for (size_t y_temp = y; y_temp < y + (cellular * 0.1) * HEIGHT && y > HEIGHT * 0.2; y_temp++) {
			blocksData[x][y_temp][z].isSolid = true;
			blocksData[x][y_temp][z].color = grass;
			blocksData[x][y_temp][z].position = glm::vec3(x, y_temp, z);
		}

		// Add snow peaks
		for (size_t y_temp = y; y_temp < y + (simplex * 0.1 -0.02) * HEIGHT && y > HEIGHT * 0.6; y_temp++) {
			blocksData[x][y_temp][z].isSolid = true;
			blocksData[x][y_temp][z].color = snow;
			blocksData[x][y_temp][z].position = glm::vec3(x, y_temp, z);
		}

		

		// Add caves
		for (size_t y = 0; y < HEIGHT; y++) {
			if (!blocksData[x][y][z].isSolid) {
				break;
			}


			//std::cout << perlinNoise.GetNoise((float)x, (float)y, (float)z) << std::endl;
			
			if (perlinNoise.GetNoise((float)x, (float)y, (float)z) > 0.4) {
				blocksData[x][y][z].isSolid = false;
			}
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
