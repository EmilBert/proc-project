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
	Vertex{glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, 0.0f),	 glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
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
		blocks[x][y][z] = Block(((float)rand() / RAND_MAX > 0.9), glm::vec3(x,y,z), glm::vec3(1.0f, 1.0f, 1.0f));
	}

	GenerateMesh();
}

Chunk::Chunk(glm::vec3 pos, std::vector<std::vector<std::vector<bool>>>& data)
{
	position = { WIDTH * pos.x, pos.y, WIDTH * pos.z };

	for (size_t y = 0; y < HEIGHT; y++)
	for (size_t x = 0; x < WIDTH; x++)
	for (size_t z = 0; z < WIDTH; z++)
	{
		blocks[x][y][z] = Block(data[x + (int)position.x]
									[y]
									[z + (int)position.z], 
									glm::vec3(x, y, z), 
									glm::vec3(1.0f, 1.0f, 1.0f));
	}

	GenerateMesh();
}

Chunk::Chunk(glm::vec3 pos, std::vector<std::vector<std::vector<Block>>>& data) {
	position = { WIDTH * pos.x, pos.y, WIDTH * pos.z };

	for (size_t y = 0; y < HEIGHT; y++)
	for (size_t x = 0; x < WIDTH; x++)
	for (size_t z = 0; z < WIDTH; z++)
	{
		blocks[x][y][z].isSolid = data[(int)position.x + x][y][(int)position.z + z].isSolid;
		blocks[x][y][z].isTransparent = data[(int)position.x + x][y][(int)position.z + z].isTransparent;
		blocks[x][y][z].color	= data[(int)position.x + x][y][(int)position.z + z].color;
		//std::cout << blocks[x][y][z].color.x << blocks[x][y][z].color.y << blocks[x][y][z].color.z << std::endl;
		blocks[x][y][z].position = glm::vec3(x, y, z);
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
void Chunk::ExtractFace(Vertex vertices[], Block data ,std::vector<Vertex> &verts, std::vector<GLuint> &inds)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, data.position);

	for (size_t i = 0; i < 4; i++)
	{
		auto vp		= model * glm::vec4(vertices[i].vertices, 1);
		Vertex v	= vertices[i];
		v.vertices	= vp;
		v.color		= data.color;
		verts.push_back(v);
	}

	for (size_t i = 0; i < 6; i++)
	{
		inds.push_back(face_inds[i] + index_depth);
	}
	index_depth += 4;
}

// Generate a mesh and store it in the chunkMesh member variable
void Chunk::GenerateMesh()
{

	std::vector<Vertex> verts;
	std::vector<GLuint> inds;

	index_depth = 0;
	for (size_t y = 0; y < HEIGHT; y++)
	for (size_t x = 0; x < WIDTH; x++)
	for (size_t z = 0; z < WIDTH; z++)
	{
		// Is this Block solid?
		if (blocks[x][y][z].isSolid) 
		{
			//Check right and left
			if ((x < WIDTH-1 && !blocks[x + 1][y][z].isSolid) || x == WIDTH - 1) {
				ExtractFace(right_verts, blocks[x][y][z], verts, inds);
			}
			if ((x > 0	&& !blocks[x - 1][y][z].isSolid) || x == 0)	{
				ExtractFace(left_verts, blocks[x][y][z], verts, inds);
			}
			//Check top and bottom
			if ((y < HEIGHT-1 && !blocks[x][y + 1][z].isSolid) || y == HEIGHT - 1){
				ExtractFace(top_verts, blocks[x][y][z], verts, inds);
			}
			if ((y > 0	&& !blocks[x][y - 1][z].isSolid) || y == 0)	{
				ExtractFace(bottom_verts, blocks[x][y][z], verts, inds);
			}
			//Check front and back
			if ((z < WIDTH-1 && !blocks[x][y][z + 1].isSolid) || z == WIDTH - 1) {
				ExtractFace(front_verts, blocks[x][y][z], verts, inds);
			}
			if ((z > 0	&& !blocks[x][y][z - 1].isSolid) || z == 0)	{
				ExtractFace(back_verts, blocks[x][y][z], verts, inds);
			}
		}
	}

	chunkMesh = Mesh(verts, inds, position);
	GenerateWaterMesh();
}

void Chunk::GenerateWaterMesh()
{
	index_depth = 0;

	std::vector<Vertex> verts;
	std::vector<GLuint> inds;

	for (size_t y = 0; y < HEIGHT; y++)
	for (size_t x = 0; x < WIDTH; x++)
	for (size_t z = 0; z < WIDTH; z++)
	{

		// Is this Block transparent?
		if (blocks[x][y][z].isTransparent)
		{
					////Check right and left
					/*if ((x < WIDTH - 1 && !blocks[x + 1][y][z].isTransparent) || x == WIDTH - 1) {
						ExtractFace(right_verts, blocks[x][y][z], verts, inds);
					}
					if ((x > 0 && !blocks[x - 1][y][z].isTransparent) || x == 0) {
						ExtractFace(left_verts, blocks[x][y][z], verts, inds);
					}*/
					//Check top and bottom
					if ((y < HEIGHT - 1 && !blocks[x][y + 1][z].isTransparent) || y == HEIGHT - 1) {
						ExtractFace(top_verts, blocks[x][y][z], verts, inds);
					}
					/*if ((y > 0 && !blocks[x][y - 1][z].isTransparent) || y == 0) {
						ExtractFace(bottom_verts, blocks[x][y][z], verts, inds);
					}*/
					////Check front and back
					/*if ((z < WIDTH - 1 && !blocks[x][y][z + 1].isTransparent) || z == WIDTH - 1) {
						ExtractFace(front_verts, blocks[x][y][z], verts, inds);
					}
					if ((z > 0 && !blocks[x][y][z - 1].isTransparent) || z == 0) {
						ExtractFace(back_verts, blocks[x][y][z], verts, inds), verts, inds;
					}*/
		}

	}
		waterMesh = Mesh(verts, inds, position);
}


void Chunk::Draw(Shader & shader, Camera & camera)
{
	chunkMesh.Draw(shader, camera);
}

void Chunk::DrawWater(Shader& shader, Camera& camera)
{
	waterMesh.Draw(shader, camera);
}




