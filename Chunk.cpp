#include "Chunk.h"
#include <random>


Chunk::Chunk()
{
	for (int x = 0; x < WIDTH; x++)
	{
		for (int z = 0; z < WIDTH; z++)
		{
			for (int y = 0; y < HEIGHT; y++)
			{
				BlockData bd;
				bd.solid = ((float)rand() / RAND_MAX > 0.5);
				bd.position = glm::vec3(x, y, z);
				blocks.push_back(bd);
				blockRenderer.push_back(Block(glm::vec3(x, y, z)));
			}
		}
	}
}

void Chunk::Draw(Shader& shader, Camera& camera)
{
	for (int i = 0; i < WIDTH * WIDTH * HEIGHT; i++)
	{
		if (blocks[i].solid) {
			
			blockRenderer[i].Draw(shader, camera);
		}
	}
}
