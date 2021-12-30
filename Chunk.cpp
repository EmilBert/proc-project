#include "Chunk.h"
#include <random>
// Top
Vertex Chunk::top_verts[] =
{
	Vertex{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f)}
};

// Bottom
Vertex Chunk::bottom_verts[] =
{
	Vertex{glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(0.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f)}
};

// Right
Vertex Chunk::right_verts[] =
{
	Vertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)}
};

// Left
Vertex Chunk::left_verts[] =
{
	Vertex{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(0.0f, -1.0f, 1.0f), glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 1.0f)}
};

// Front
Vertex Chunk::front_verts[] =
{
	Vertex{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(0.0f, -1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f)}
};

// Back
Vertex Chunk::back_verts[] =
{ //                |   COORDINATES   |			 |     NORMALS    |			  |		COLORS	   |			| TexCoord |
	Vertex{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)}
};

GLuint Chunk::face_inds[] =
{
	0, 1, 2,
	3, 2, 1
};

Chunk::Chunk(glm::vec3 pos)
{
	position = { WIDTH * pos.x, pos.y, WIDTH * pos.z };

	for (size_t y = 0; y < HEIGHT; y++)
	for (size_t x = 0; x < WIDTH;  x++)
	for (size_t z = 0; z < WIDTH;  z++)
	{
		blocks[x][y][z] = Block(((float)rand() / RAND_MAX > 0.9), glm::vec3(x,y,z));
	}

	GenerateMesh();
}

Chunk::Chunk(glm::vec3 pos, std::vector<std::vector<int>>& data)
{
	position = { WIDTH * pos.x, pos.y, WIDTH * pos.z };

	for (size_t y = 0; y < HEIGHT; y++)
	for (size_t x = 0; x < WIDTH; x++)
	for (size_t z = 0; z < WIDTH; z++)
	{
		blocks[x][y][z] = Block((data[x + (int)position.x][z + (int)position.z] >= y), glm::vec3(x, y, z));
	}

	GenerateMesh();
}

Chunk::Chunk(Block data[WIDTH][HEIGHT][WIDTH])
{


	for (size_t y = 0; y < HEIGHT; y++)
	for (size_t x = 0; x < WIDTH; x++)
	for (size_t z = 0; z < WIDTH; z++)
	{
		blocks[x][y][z] = data[x][y][z];
	}
	GenerateMesh();
}

//vertices = std::vector<Vertex>(block_vertices, block_vertices + sizeof(block_vertices) / sizeof(Vertex));
//indices = std::vector<GLuint>(block_indices, block_indices + sizeof(block_indices) / sizeof(GLuint));

// Extract the given face and put its
// vertices and indices in their respective vector
void Chunk::ExtractFace(Vertex vertices[], glm::vec3 pos)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, pos);

	for (size_t i = 0; i < 4; i++)
	{
		auto vp = model * glm::vec4(vertices[i].vertices, 1);
		Vertex v = vertices[i];
		v.vertices = vp;
		v.color = glm::vec3(1.0f, 0.0f, 1.0f);
		Chunk::verts.push_back(v);
	}

	for (size_t i = 0; i < 6; i++)
	{
		Chunk::inds.push_back(face_inds[i] +index_depth);
	}
	index_depth += 4;
}

// Generate a mesh and store it in the chunkMesh member variable
void Chunk::GenerateMesh()
{
	index_depth = 0;

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
				ExtractFace(right_verts, blocks[x][y][z].position);
			}
			if ((x > 0	&& !blocks[x - 1][y][z].isSolid) || x == 0)			
			{
				ExtractFace(left_verts, blocks[x][y][z].position);
			}
			//Check top and bottom
			if ((y < HEIGHT-1 && !blocks[x][y + 1][z].isSolid) || y == HEIGHT - 1)
			{
				ExtractFace(top_verts, blocks[x][y][z].position);
			}
			if ((y > 0	&& !blocks[x][y - 1][z].isSolid) || y == 0)			
			{
				ExtractFace(bottom_verts, blocks[x][y][z].position);
			}
			//Check front and back
			if ((z < WIDTH-1 && !blocks[x][y][z + 1].isSolid) || z == WIDTH - 1) 
			{
				ExtractFace(front_verts, blocks[x][y][z].position);
			}
			if ((z > 0	&& !blocks[x][y][z - 1].isSolid) || z == 0)			
			{
				ExtractFace(back_verts, blocks[x][y][z].position);
			}
		}
	}

	chunkMesh = Mesh(Chunk::verts, Chunk::inds, position);
}

void changeVertColors(Vertex verts[]) {
}


void Chunk::Draw(Shader& shader, Camera& camera)
{
	chunkMesh.Draw(shader, camera);
}



