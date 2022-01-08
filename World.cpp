#include "World.h"
#include <FastNoise/FastNoiseLite.hpp>

glm::vec3 World::sand	= glm::vec3(0.76, 0.69, 0.5);
glm::vec3 World::grass	= glm::vec3(0.0, 0.60f, 0.09);
glm::vec3 World::moss	= glm::vec3(0.0, 0.40f, 0.07);
glm::vec3 World::stone	= glm::vec3(0.392, 0.392, 0.392);
glm::vec3 World::snow	= glm::vec3(0.8, 0.8, 1.0);
glm::vec3 World::ice	= glm::vec3(0.4, 0.6, 1.0);
glm::vec3 World::clay	= glm::vec3(0.91, 0.64, 0.50);
glm::vec3 World::water	= glm::vec3(0.2, 0.2, 1);



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
	blocksHeightMap = std::vector<std::vector<std::pair<int, BiomeType> >>(range * WIDTH, std::vector<std::pair<int, BiomeType>> (range * WIDTH, std::pair<int,BiomeType>(1, hills)));
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

			blocksHeightMap[x][z].first = (int)(((temp+1)/2 )*HEIGHT);
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
	simplexNoise.SetFrequency(0.015);

	FastNoiseLite perlinNoise;
	perlinNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	perlinNoise.SetFrequency(0.015);

	FastNoiseLite valueNoise;
	valueNoise.SetNoiseType(FastNoiseLite::NoiseType_Value);
	valueNoise.SetFrequency(0.015);
	valueNoise.SetFractalOctaves(8);
	valueNoise.SetDomainWarpAmp(50);
	valueNoise.SetFractalGain(20);
	valueNoise.SetSeed(1337);

	FastNoiseLite simplexNoise3D;
	simplexNoise3D.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	simplexNoise3D.SetFrequency(0.01);

	FastNoiseLite cubicNoise;
	cubicNoise.SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);
	cubicNoise.SetFrequency(0.020);
	cubicNoise.SetFractalOctaves(5);

	FastNoiseLite cubicWarp;
	cubicWarp.SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);
	cubicWarp.SetFrequency(0.020);
	cubicWarp.SetFractalOctaves(5);
	
	cubicWarp.SetDomainWarpType(FastNoiseLite::DomainWarpType_OpenSimplex2Reduced);
	cubicWarp.SetDomainWarpAmp(30);
	cubicWarp.SetFrequency(0.010);
	
	cubicWarp.SetFractalType(FastNoiseLite::FractalType::FractalType_DomainWarpIndependent);
	cubicWarp.SetFractalOctaves(5);
	cubicWarp.SetFractalLacunarity(2);
	cubicWarp.SetFractalGain(0.5);

	FastNoiseLite cellularNoise;
	cellularNoise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
	cellularNoise.SetFrequency(0.01);
	cellularNoise.SetFractalType(FastNoiseLite::FractalType_PingPong);

	FastNoiseLite biomeNoise;
	biomeNoise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
	biomeNoise.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Hybrid);
	biomeNoise.SetCellularReturnType(FastNoiseLite::CellularReturnType_CellValue);
	biomeNoise.SetFrequency(0.0075);

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
	
	
	float noise = 0;
	glm::vec3 blockColor = stone;

	for (size_t x = 0; x < WIDTH * range; x++)
	for (size_t z = 0; z < WIDTH * range; z++)
	{
		float xf = x;
		float zf = z;
		biomeWarp.DomainWarp(xf, zf);

		float xc = x;
		float zc = z;
		cubicWarp.DomainWarp(xc, zc);

		//Height creation
		float cubic		= (cubicNoise.GetNoise(		(float)xc,	(float)zc) + 1) / 2;
		float simplex	= (simplexNoise.GetNoise(	(float)x,	(float)z) + 1) / 2;
		float value		= (valueNoise.GetNoise(		(float)x,	(float)z) + 1) / 2;
		float cellular	= (cellularNoise.GetNoise(	(float)x,	(float)z) + 1) / 2;
		float biome		= (biomeNoise.GetNoise(				xf,		zf) + 1) / 2;
		float perlin	= (perlinNoise.GetNoise(	(float)x,	(float)z) + 1) / 2;

		BiomeType type = hills;
		//Decide biome & set settings
		if (biome > 0.8) { //hills
			noise = cubic * 0.8 + perlin * 0.1 + 0.1;
			type = hills;
		}
		else if (biome > 0.5) { // desert
			noise = cellular * 0.2 + simplex * 0.1 + 0.2;
			type = desert;
		}
		else if (biome > 0.0) {// ocean
			noise = 0.05;
			type = ocean;
		}
		
		//noise = value*0.8 + perlin * 0.1 + 0.1;

		blocksHeightMap[x][z].first = (noise)* HEIGHT;
		blocksHeightMap[x][z].second = type;
		
		if (blocksHeightMap[x][z].first == 0) blocksHeightMap[x][z].first = 1;
	}


	int smoothRange = 10;
	for (size_t x = smoothRange; x < WIDTH * range - smoothRange; x++)
	for (size_t z = smoothRange; z < WIDTH * range - smoothRange; z++)
	{
		int heightTotal  = 0;
		int smoothLength = smoothRange * 2 + 1;

		if (x == smoothRange && z == smoothRange) {
			blocksHeightMap[x][z].first = HEIGHT;
			continue;
		}
		for (size_t x2 = x - smoothRange; x2 < x + smoothRange; x2++)
		for (size_t z2 = z - smoothRange; z2 < z + smoothRange; z2++)
		{
			heightTotal += blocksHeightMap[x2][z2].first;
		}
		blocksHeightMap[x][z].first = heightTotal / (smoothLength*smoothLength);
		if (blocksHeightMap[x][z].first == 0) blocksHeightMap[x][z].first = 1;
	}

	for (size_t x = smoothRange; x < WIDTH * range - smoothRange; x++)
		for (size_t z = smoothRange; z < WIDTH * range - smoothRange; z++)
		{

			//Decide biome & set settings
			switch (blocksHeightMap[x][z].second)
			{
			case hills:
				blockColor = grass;
				break;
			case desert:
				blockColor = sand;
				break;
			case mesa:
				blockColor = clay;
				break;
			case glacier:
				blockColor = ice;
				break;
			case forest:
				blockColor = moss;
				break;
			case mountains:
				blockColor = snow;
				break;
			case ocean:
				blockColor = sand;
				break;
			default:
				blockColor = stone;
				break;
			}

			size_t y = 0;
			for (; y < blocksHeightMap[x][z].first; y++)
			{
				blocksData[x][y][z].isSolid = true;
				blocksData[x][y][z].color = blockColor;
				blocksData[x][y][z].position = glm::vec3(x, y, z);
			}

			//Add ocean
			for (; y < 25; y++)
			{
					blocksData[x][y][z].isSolid = false;
					blocksData[x][y][z].isTransparent = true;
					blocksData[x][y][z].color = water;
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
	for (int i = 0; i < chunks.size(); i++)
	{
		chunks[i].DrawWater(shader, camera);
	}
}
