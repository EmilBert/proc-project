#include "Chunk.h"
#include <random>
// Top
static Vertex top_verts[] =
{
	Vertex{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f)},
};

// Bottom
static Vertex bottom_verts[] =
{
	Vertex{glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(0.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f)},
};

// Right
static Vertex right_verts[] =
{
	Vertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
};

// Left
static Vertex left_verts[] =
{
	Vertex{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(0.0f, -1.0f, 1.0f), glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
};

// Front
static Vertex front_verts[] =
{
	Vertex{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(0.0f, -1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f)},
};

// Back
static Vertex back_verts[] =
{ //                |   COORDINATES   |			 |     NORMALS    |			  |		COLORS	   |			| TexCoord |
	Vertex{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)}
};

GLuint face_inds[] =
{
	0, 1, 2,
	3, 2, 1,
};

Chunk::Chunk()
{
	for (size_t y = 0; y < HEIGHT; y++)
	for (size_t x = 0; x < WIDTH;  x++)
	for (size_t z = 0; z < WIDTH;  z++)
	{
		blocks[x][y][z] = Block(true, glm::vec3(x,y,z));
	}
}

Chunk::Chunk(Block data[WIDTH][HEIGHT][WIDTH])
{
	for (size_t y = 0; y < HEIGHT; y++)
	for (size_t x = 0; x < WIDTH; x++)
	for (size_t z = 0; z < WIDTH; z++)
	{
		blocks[x][y][z] = data[x][y][z];
	}
}

// Extract the given face and put its
// vertices and indices in their respective vector
void Chunk::ExtractFace(Vertex vertices[])
{
	for (size_t i = 0; i < 4; i++)
	{
		Chunk::verts.push_back(vertices[i]);
	}

	for (size_t i = 0; i < 6; i++)
	{
		Chunk::inds.push_back(face_inds[i]);
	}
}

// Generate a mesh and store it in the chunkMesh member variable
void Chunk::GenerateMesh()
{
	for (size_t y = 0; y < HEIGHT; y++)
	for (size_t x = 0; x < WIDTH; x++)
	for (size_t z = 0; z < WIDTH; z++)
	{
		// Is this Block solid?
		if (blocks[x][y][z].isSolid) 
		{
			//Check right and left
			if ((x < WIDTH-1 && !blocks[x + 1][y][z].isSolid) || x == WIDTH - 1) 
			{
				ExtractFace(right_verts);
			}
			if ((x > 0	&& !blocks[x - 1][y][z].isSolid) || x == 0)			
			{
				ExtractFace(left_verts);
			}
			//Check top and bottom
			if ((y < HEIGHT-1 && !blocks[x][y + 1][z].isSolid) || y == HEIGHT - 1)
			{
				ExtractFace(top_verts);
			}
			if ((y > 0	&& !blocks[x][y - 1][z].isSolid) || y == 0)			
			{
				ExtractFace(bottom_verts);
			}
			//Check front and back
			if ((z < WIDTH-1 && !blocks[x][y][z + 1].isSolid) || z == WIDTH - 1) 
			{
				ExtractFace(front_verts);
			}
			if ((z > 0	&& !blocks[x][y][z - 1].isSolid) || z == 0)			
			{
				ExtractFace(back_verts);
			}
		}
	}

	chunkMesh = Mesh(Chunk::verts, Chunk::inds);
}

void Chunk::Draw(Shader& shader, Camera& camera)
{
	chunkMesh.Draw(shader, camera);
}



