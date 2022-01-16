#include "World.h"
#include <FastNoise/FastNoiseLite.hpp>

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



World::World()
{
	World(3, 0);
}

World::World(int r, int seed) : range(r), noise_seed(seed)
{
	blocksHeightMap = std::vector<std::vector<std::pair<int, BiomeType> >>(range * WIDTH, std::vector<std::pair<int, BiomeType>> (range * WIDTH, std::pair<int,BiomeType>(1, hills)));
	blocksData		= std::vector<std::vector<std::vector<Block>>>(range * WIDTH, std::vector<std::vector<Block>>(HEIGHT, std::vector<Block>(range * WIDTH, Block())));
	
	GenerateHeightMap();
	std::cout << "Done with Heightmap!" << std::endl;
	Generate3DBlocks();
	std::cout << "Done with 3D Grid!" << std::endl;

	for (size_t x = 0; x < range; x++) {
		for (size_t z = 0; z < range; z++) {
			chunks.push_back(Chunk(glm::vec3(x, 0, z), blocksData, range));
		}
	}
}

void World::GenerateHeightMap()
{
	FastNoiseLite simplexNoise;
	simplexNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
	simplexNoise.SetFrequency(0.015);

	FastNoiseLite perlinNoise;
	perlinNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	perlinNoise.SetFrequency(0.015);

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
	biomeNoise.SetSeed(noise_seed);
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

	FastNoiseLite perlinMountainsNoise;
	perlinMountainsNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	perlinMountainsNoise.SetFractalType(FastNoiseLite::FractalType_PingPong);
	perlinMountainsNoise.SetFrequency(0.002);

	FastNoiseLite cellularMountainsNoise;
	cellularMountainsNoise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
	cellularMountainsNoise.SetFrequency(0.05);

	FastNoiseLite perlinMesaNoise;
	perlinMesaNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	perlinMesaNoise.SetFractalType(FastNoiseLite::FractalType_FBm);
	perlinMesaNoise.SetFrequency(0.010);

	for (size_t x = 0; x < WIDTH * range; x++)
		for (size_t z = 0; z < WIDTH * range; z++)
		{
			// Get Biome
			float xf = x;
			float zf = z;
			biomeWarp.DomainWarp(xf, zf);
			float biome = (biomeNoise.GetNoise(xf, zf) + 1) / 2;

			// Default biome
			BiomeType type = hills;
			float noise = 0;

			//Decide biome & set settings
			if (biome > 0.8) { //hills
				float xc = x;
				float zc = z;
				cubicWarp.DomainWarp(xc, zc);
				float cubic = (cubicNoise.GetNoise((float)xc, (float)zc) + 1) / 2;
				float perlin = (perlinNoise.GetNoise((float)x, (float)z) + 1) / 2;
				noise = cubic * 0.5 + perlin * 0.2 + 0.1;
				type = hills;
			}
			else if (biome > 0.6) { //Forest
				float xc = x;
				float zc = z;
				cubicWarp.DomainWarp(xc, zc);
				float cubic = (cubicNoise.GetNoise((float)xc, (float)zc) + 1) / 2;
				float perlin = (perlinNoise.GetNoise((float)x, (float)z) + 1) / 2;
				noise = cubic * 0.5 + perlin * 0.2 + 0.1;
				type = forest;
			}

			else if (biome > 0.5) { // desert
				float simplex = (simplexNoise.GetNoise((float)x, (float)z) + 1) / 2;
				float cellular = (cellularNoise.GetNoise((float)x, (float)z) + 1) / 2;
				noise = cellular * 0.1 + simplex * 0.1 + 0.2;
				type = desert;
			}

			else if (biome > 0.4) { // Mesa
				float perlin  = (perlinMesaNoise.GetNoise((float)x, (float)z) + 1) / 2;
				noise = perlin * 0.9;
				if (noise > 0.55) noise += 0.30;
				type = mesa;
			}

			else if (biome > 0.2) { // Mountains
				float perlinMountains = (perlinMountainsNoise.GetNoise((float)x, (float)z) + 1) / 2;
				float cellularMountains = (cellularMountainsNoise.GetNoise((float)x, (float)z) + 1) / 2;

				noise = cellularMountains + 0.5 * perlinMountains + 0.5;
				type = mountains;
			}

			else if (biome > 0.0) {// ocean
				noise = 0.05;
				type = ocean;
			}

			//noise = value*0.8 + perlin * 0.1 + 0.1;

			blocksHeightMap[x][z].first = (noise)*HEIGHT;
			blocksHeightMap[x][z].second = type;
			
			if (blocksHeightMap[x][z].first < 0)		blocksHeightMap[x][z].first = 1;
			if (blocksHeightMap[x][z].first > HEIGHT)	blocksHeightMap[x][z].first = HEIGHT;

		}


	int smoothRange = 8;
	int smoothLength = smoothRange * 2 + 1;
	for (int x = 0; x < WIDTH * range; x++)
	for (int z = 0; z < WIDTH * range; z++)
	{
		int heightTotal = 0;
		int outOfBounds = 0;

		for (int x2 = x - smoothRange; x2 < x + smoothRange; x2++)
		for (int z2 = z - smoothRange; z2 < z + smoothRange; z2++)
		{
			if (x2 < 0 || z2 < 0 || x2 >= WIDTH * range || z2 >= WIDTH * range) {
				outOfBounds += blocksHeightMap[x][z].first;
			}
			else {
				heightTotal += blocksHeightMap[x2][z2].first;
			}
		}
		blocksHeightMap[x][z].first = (heightTotal + outOfBounds) / (smoothLength * smoothLength);
	}
}

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

		//std::vector<Block>;

		//Decide biome & set settings
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
				blocksData[x][y][z] = Block(true, glm::vec3(x, y ,z), grass);
				blocksData[x][y +1][z] = Block(true, glm::vec3(x, y + 1, z), grass);
				blocksData[x][y +2][z] = Block(true, glm::vec3(x, y + 2, z), grass);
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

		// Add ocean
		for (; y < 20; y++)
		{
			blocksData[x][y][z] = Block(false, glm::vec3(x, y, z), water);
			blocksData[x][y][z].isTransparent = true;
		}
	}
}

void World::InsertBlock(Block in)
{
	int x = in.position.x;
	int y = in.position.y;
	int z = in.position.z;
	blocksData[x][y][z] = in;
}

void World::GrowTree(glm::vec3 pos) {
	
	int x = pos.x;
	int y = pos.y;
	int z = pos.z;
	
	if (x < 1 || x > WIDTH*range - 2 || z < 1 || z > WIDTH * range - 2) return;

	for (int y_ = y; y_ < y + 5; y_++)
		blocksData[x][y_][z] = Block(true, glm::vec3(x,y_,z), dirt);
	

	for (int x_ = x-1; x_ < x + 2; x_++)
	for (int z_ = z-1; z_ < z + 2; z_++)
	for (int y_ = y+3; y_ < y + 5; y_++)
		blocksData[x_][y_][z_] = Block(true, glm::vec3(x_, y_, z_), grass);
	
		
	blocksData[x-1][y+5][z]		= Block(true,	glm::vec3(x-1, y+5, z),		grass);
	blocksData[x][y + 5][z-1]	= Block(true,	glm::vec3(x, y + 5, z-1),	grass);
	blocksData[x+1][y + 5][z]	= Block(true,	glm::vec3(x+1, y + 5, z),	grass);
	blocksData[x][y + 5][z+1]	= Block(true,	glm::vec3(x, y + 5, z+1),	grass);
	blocksData[x][y + 5][z]		= Block(true,	glm::vec3(x, y + 5, z),		grass);
	


}

void World::Draw(Shader& shader, Shader& waterShader, Camera& camera)
{
	for (int i = 0; i < chunks.size(); i++)
	{
		chunks[i].Draw(shader, camera);
	}
	for (int i = 0; i < chunks.size(); i++)
	{
		chunks[i].DrawWater(waterShader, camera);
	}
}
