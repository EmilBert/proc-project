#include "World.h"
#include <FastNoise/FastNoiseLite.hpp>

glm::vec3 World::sand	= glm::vec3(0.76, 0.69, 0.5);
glm::vec3 World::grass	= glm::vec3(0.0, 0.60f, 0.09);
glm::vec3 World::moss	= glm::vec3(0.0, 0.40f, 0.07);
glm::vec3 World::stone	= glm::vec3(0.392, 0.392, 0.392);
glm::vec3 World::snow	= glm::vec3(0.8, 0.8, 1.0);
glm::vec3 World::ice	= glm::vec3(0.4, 0.6, 1.0);
glm::vec3 World::clay	= glm::vec3(0.91, 0.64, 0.50);
glm::vec3 World::water	= glm::vec3(0.1, 0.1, 0.9);

enum biomeType
{
	hills		= 0,
	desert		= 1,
	mesa		= 2,
	glacier		= 3,
	forest		= 4,
	mountains	= 5,
	ocean		= 6
};

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
	//blocks = std::vector<std::vector<std::vector<bool>>>(range * WIDTH, std::vector<std::vector<bool>>(HEIGHT, std::vector<bool>(range*WIDTH, false)));
	blocksHeightMap = std::vector<std::vector<int>>(range * WIDTH, std::vector<int>(range * WIDTH, 1));
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
	simplexNoise.SetFrequency(0.005);

	FastNoiseLite perlinNoise;
	perlinNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	perlinNoise.SetFrequency(0.05);

	FastNoiseLite valueNoise;
	valueNoise.SetNoiseType(FastNoiseLite::NoiseType_Value);
	valueNoise.SetFrequency(0.0015);
	valueNoise.SetFractalOctaves(8);
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

	FastNoiseLite biomeNoise;
	biomeNoise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
	biomeNoise.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Hybrid);
	biomeNoise.SetCellularReturnType(FastNoiseLite::CellularReturnType_CellValue);
	biomeNoise.SetFrequency(0.010);

	biomeNoise.SetCellularJitter(1);
	biomeNoise.SetDomainWarpType(FastNoiseLite::DomainWarpType_OpenSimplex2);
	biomeNoise.SetDomainWarpAmp(100);
	
	biomeNoise.SetFractalType(FastNoiseLite::FractalType_DomainWarpIndependent);
	biomeNoise.SetFractalOctaves(3);
	biomeNoise.SetFractalLacunarity(2);
	biomeNoise.SetFractalGain(0.5);
	biomeNoise.SetCellularReturnType(FastNoiseLite::CellularReturnType_CellValue);

	FastNoiseLite biomeWarp;
	biomeWarp.SetCellularJitter(1);
	biomeWarp.SetDomainWarpType(FastNoiseLite::DomainWarpType_OpenSimplex2);
	biomeWarp.SetDomainWarpAmp(100);
	biomeWarp.SetFrequency(0.015);

	biomeWarp.SetFractalType(FastNoiseLite::FractalType_DomainWarpIndependent);
	biomeWarp.SetFractalOctaves(3);
	biomeWarp.SetFractalLacunarity(2);
	biomeWarp.SetFractalGain(0.5);
	biomeWarp.SetCellularReturnType(FastNoiseLite::CellularReturnType_CellValue);
	
	
	float currentNoise1 = 0;
	float currentNoise2 = 0;
	glm::vec3 blockColor = stone;

	for (size_t x = 0; x < WIDTH * range; x++)
	for (size_t z = 0; z < WIDTH * range; z++)
	{
		float xf = x;
		float zf = z;

		biomeWarp.DomainWarp(xf, zf);
		//Height creation
		float cubic		= (cubicNoise.GetNoise(		(float)x,	(float)z) + 1) / 2;
		float simplex	= (simplexNoise.GetNoise(	(float)x,	(float)z) + 1) / 2;
		float value		= (valueNoise.GetNoise(		(float)x,	(float)z) + 1) / 2;
		float cellular	= (cellularNoise.GetNoise(	(float)x,	(float)z) + 1) / 2;
		float biome		= (biomeNoise.GetNoise(				xf,		zf) + 1) / 2;
		//float simplex	= (simplexNoise.GetNoise(	(float)x,	(float)z) + 1) / 4;

		

		//Decide biome & set settings
		if (biome > 0.9) { // Glacier
			currentNoise2 = currentNoise1;
			currentNoise1 = simplex;
			blockColor	  =	ice;

		}else if (biome > 0.7) { //Hills
			currentNoise2 = currentNoise1;
			currentNoise1 = value;
			blockColor = grass;
		}
		else if (biome > 0.6) { // Desert
			currentNoise2 = currentNoise1;
			currentNoise1 = cellular;
			blockColor = sand;
		}
		else if (biome > 0.5) {// Ocean
			currentNoise2 = currentNoise1;
			currentNoise1 = simplex;
			blockColor = water;
		}
		else if (biome > 0.4) {// Mesa
			currentNoise2 = currentNoise1;
			currentNoise1 = cubic;
			blockColor = clay;
		}
		else if (biome > 0.2) { // Mountains
			currentNoise2 = currentNoise1;
			currentNoise1 = value;
			blockColor = snow;
		}
		else if (biome > 0.0) { // Forest
			currentNoise2 = currentNoise1;
			currentNoise1 = simplex;
			blockColor = moss;
		}
		
		//Blend biomes
		float useNoise;
		if (currentNoise1 > currentNoise2) {
			useNoise = currentNoise1;
		}
		else {
			useNoise = currentNoise2;
		}
		
		blocksHeightMap[x][z] = useNoise * HEIGHT * 0.9;
	}

	

	int smoothRange = 10;
	for (size_t x = smoothRange; x < WIDTH * range - smoothRange; x++)
	for (size_t z = smoothRange; z < WIDTH * range - smoothRange; z++)
	{
		int heightTotal  = 0;
		int smoothLength = smoothRange * 2 + 1;
		for (size_t x2 = x - smoothRange; x2 < x + smoothRange; x2++)
		for (size_t z2 = z - smoothRange; z2 < z + smoothRange; z2++)
		{
			heightTotal += blocksHeightMap[x2][z2];
		}
		blocksHeightMap[x][z] = heightTotal / (smoothLength*smoothLength);
	}

	for (size_t x = smoothRange; x < WIDTH * range - smoothRange; x++)
	for (size_t z = smoothRange; z < WIDTH * range - smoothRange; z++)
	{
		glm::vec3 blockColor;
		float xf = x;
		float zf = z;
		biomeWarp.DomainWarp(xf, zf);
		float biome = (biomeNoise.GetNoise(xf, zf) + 1) / 2;
		//Decide biome & set settings
		if (biome > 0.9) { // Glacier
			blockColor = ice;
		}
		else if (biome > 0.7) { //Hills
			blockColor = grass;
		}
		else if (biome > 0.6) { // Desert
			blockColor = sand;
		}
		else if (biome > 0.5) {// Ocean
			blockColor = water;
		}
		else if (biome > 0.4) {// Mesa
			blockColor = clay;
		}
		else if (biome > 0.2) { // Mountains
			blockColor = snow;
		}
		else if (biome > 0.0) { // Forest
			blockColor = moss;
		}

		size_t y = 0;
		for (; y < blocksHeightMap[x][z] * 0.9; y++)
		{
			blocksData[x][y][z].isSolid = true;
			blocksData[x][y][z].color = blockColor;
			blocksData[x][y][z].position = glm::vec3(x, y, z);
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
