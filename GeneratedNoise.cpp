#include "GeneratedNoise.h"


GeneratedNoise::GeneratedNoise()
{
	GeneratedNoise(1);
}

GeneratedNoise::GeneratedNoise(int seed)
{
	simplexNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
	simplexNoise.SetFrequency(0.015);

	perlinNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	perlinNoise.SetFrequency(0.015);

	simplexNoise3D.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	simplexNoise3D.SetFrequency(0.01);

	cubicNoise.SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);
	cubicNoise.SetFrequency(0.020);
	cubicNoise.SetFractalOctaves(5);

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

	cellularNoise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
	cellularNoise.SetFrequency(0.01);
	cellularNoise.SetFractalType(FastNoiseLite::FractalType_PingPong);

	biomeNoise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
	biomeNoise.SetSeed(seed);
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

	biomeWarp.SetCellularJitter(1);
	biomeWarp.SetDomainWarpType(FastNoiseLite::DomainWarpType_OpenSimplex2);
	biomeWarp.SetDomainWarpAmp(100);
	biomeWarp.SetFrequency(0.015);

	biomeWarp.SetFractalType(FastNoiseLite::FractalType_DomainWarpIndependent);
	biomeWarp.SetFractalOctaves(3);
	biomeWarp.SetFractalLacunarity(2);
	biomeWarp.SetFractalGain(0.5);
	biomeWarp.SetCellularReturnType(FastNoiseLite::CellularReturnType_CellValue);

	perlinMountainsNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	perlinMountainsNoise.SetFractalType(FastNoiseLite::FractalType_PingPong);
	perlinMountainsNoise.SetFrequency(0.002);

	cellularMountainsNoise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
	cellularMountainsNoise.SetFrequency(0.05);

	perlinMesaNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	perlinMesaNoise.SetFractalType(FastNoiseLite::FractalType_FBm);
	perlinMesaNoise.SetFrequency(0.010);
}

std::pair<int, BiomeType> GeneratedNoise::GetHeight(int x, int z, int maxHeight)
{
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
		float perlin = (perlinMesaNoise.GetNoise((float)x, (float)z) + 1) / 2;
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

	int finalVal = noise * maxHeight;

	finalVal = (finalVal < 1) ? 1 : finalVal;
	finalVal = (finalVal > maxHeight) ? maxHeight : finalVal;
		

	return std::pair<int, BiomeType>(finalVal,type);
}
