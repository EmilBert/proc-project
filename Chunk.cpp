#include "Chunk.h"
#include <random>
// Top
Vertex Chunk::top_verts[] =
{
	Vertex{glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)}
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

//vertices = std::vector<Vertex>(block_vertices, block_vertices + sizeof(block_vertices) / sizeof(Vertex));
//indices = std::vector<GLuint>(block_indices, block_indices + sizeof(block_indices) / sizeof(GLuint));

// Extract the given face and put its
// vertices and indices in their respective vector
void Chunk::ExtractFace(Vertex vertices[], Block data ,std::vector<Vertex> &verts, std::vector<GLuint> &inds, GLuint &index_depth)
{
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(data.position.x, data.position.y, data.position.z));

	for (size_t i = 0; i < 4; i++)
	{
		auto vp		= model * glm::vec4(vertices[i].vertices, 1);
		Vertex v	= vertices[i];
		v.vertices	= (glm::vec3)vp;
		v.color		= data.color;
		verts.push_back(v);
	}

	for (size_t i = 0; i < 6; i++)
	{
		inds.push_back(face_inds[i] + index_depth);
	}
	index_depth += 4;
}

Chunk::Chunk(glm::vec2 cp, GeneratedNoise noise) : chunkPosition(cp)
{
	position = glm::vec3(chunkPosition.x * WIDTH, 0, chunkPosition.y * WIDTH);
	noise.GenerateChunkBlocks(chunkPosition.x * WIDTH, chunkPosition.y * WIDTH, blocks);
}

Chunk::~Chunk()
{
	delete& chunkMesh;
	delete& waterMesh;
	delete& blocks;
	delete& verts;
	delete& inds;
}

// Generate a mesh and store it in the chunkMesh member variable 
void Chunk::Generate()
{
	/*
		Chunk* leftChunk	= (chunkMap.find(std::make_pair(chunkPosition.x - 1, chunkPosition.y)) != chunkMap.end()) ? chunkMap[std::make_pair(chunkPosition.x - 1, chunkPosition.y)] : nullptr;
		Chunk* rightChunk	= (chunkMap.find(std::make_pair(chunkPosition.x + 1, chunkPosition.y)) != chunkMap.end()) ? chunkMap[std::make_pair(chunkPosition.x + 1, chunkPosition.y)] : nullptr;
		Chunk* infrontChunk = (chunkMap.find(std::make_pair(chunkPosition.x, chunkPosition.y - 1)) != chunkMap.end()) ? chunkMap[std::make_pair(chunkPosition.x, chunkPosition.y - 1)] : nullptr;
		Chunk* behindChunk	= (chunkMap.find(std::make_pair(chunkPosition.x, chunkPosition.y + 1)) != chunkMap.end()) ? chunkMap[std::make_pair(chunkPosition.x, chunkPosition.y + 1)] : nullptr;
	*/

	Chunk* leftChunk	=  nullptr;
	Chunk* rightChunk	=  nullptr;
	Chunk* infrontChunk =  nullptr;
	Chunk* behindChunk	=  nullptr;

	index_depth = 0;
	for (size_t x = 0; x < WIDTH;  x++)
	for (size_t y = 0; y < HEIGHT; y++)
	for (size_t z = 0; z < WIDTH;  z++)
	{
		Block *current = &blocks[x][y][z];
		
		// Is this Block solid?
		if (current->isSolid)
		{

			//Check top and bottom
			if (y < 1 || !blocks[x][y - 1][z].isSolid)
			{
				
				ExtractFace(bottom_verts, blocks[x][y][z], verts, inds, index_depth);
			}
			if (y >= HEIGHT - 1 || !blocks[x][y + 1][z].isSolid)
			{
				ExtractFace(top_verts, blocks[x][y][z], verts, inds, index_depth);
			}

			//Check left, if at edge, check neighbor if they aren't null
			if ((x > 0 && !blocks[x - 1][y][z].isSolid) || (x == 0 && leftChunk != nullptr && !leftChunk->blocks[WIDTH-1][y][z].isSolid))
			{
				ExtractFace(left_verts, blocks[x][y][z], verts, inds, index_depth);
			}
			
			//Check right, if at edge, check neighbor if they aren't null
			if ((x < WIDTH-1 && !blocks[x + 1][y][z].isSolid) || (x == WIDTH-1 && rightChunk != nullptr && !rightChunk->blocks[0][y][z].isSolid))
			{
				ExtractFace(right_verts, blocks[x][y][z], verts, inds, index_depth);
			}
			//Check behind, if at edge, check neighbor if they aren't null
			if ((z > 0 && !blocks[x][y][z - 1].isSolid) || (z == 0 && behindChunk != nullptr && !behindChunk->blocks[x][y][WIDTH - 1].isSolid))
			{
				ExtractFace(back_verts, blocks[x][y][z], verts, inds, index_depth);
			}

			//Check infront,  if at edge, check neighbor if they aren't null
			if ((z < WIDTH - 1 && !blocks[x][y][z + 1].isSolid) || (z == WIDTH - 1 && infrontChunk != nullptr && !infrontChunk->blocks[x][y][0].isSolid))
			{
				ExtractFace(front_verts, blocks[x][y][z], verts, inds, index_depth);
			}
		}
	}

	regenMesh = false;
	setMesh = true;
}

void Chunk::SetMesh()
{
	chunkMesh = Mesh(verts, inds, position);
	setMesh = false;
}

//void Chunk::GenerateWaterMesh()
//{	
//	std::vector<Vertex> verts;
//	std::vector<GLuint> inds;
//
//	int x_start = position.x;
//	int z_start = position.z;
//
//	for (size_t x = x_start; x < x_start + WIDTH; x++)
//	for (size_t z = z_start; z < z_start + WIDTH; z++)
//	for (size_t y = 0;		 y < HEIGHT;		  y++)
//	{
//		// Is this Block transparent?
//		if (blocks[x][y][z].isTransparent)
//		{
//			//Check right and left
//			if (x < 1) {
//				ExtractFace(left_verts, blocks[x][y][z], verts, inds);
//			}
//			if (x >  WIDTH - 2) {
//				ExtractFace(right_verts, blocks[x][y][z], verts, inds);
//			}
//			// Check top and bottom
//			// Removed bc water becomes weird
//			/*if (y < 1 || !blocks[x][y - 1][z].isTransparent || !blocks[x][y - 1][z].isSolid) {
//				ExtractFace(bottom_verts, blocks[x][y][z], verts, inds);
//			}*/
//			if (y > HEIGHT - 2 || !blocks[x][y + 1][z].isTransparent) {
//				ExtractFace(top_verts, blocks[x][y][z], verts, inds);
//			}
//			//Check front and back
//			if (z < 1 ) {
//				ExtractFace(back_verts, blocks[x][y][z], verts, inds);
//			}
//			if (z > WIDTH - 2 ) {
//				ExtractFace(front_verts, blocks[x][y][z], verts, inds);
//			}
//		}
//	}
//	waterMesh = Mesh(verts, inds, position);
//}

void Chunk::Draw(Shader & shader, Camera & camera)
{
	chunkMesh.Draw(shader, camera);
}

void Chunk::DrawWater(Shader& shader, Camera& camera)
{
	waterMesh.Draw(shader, camera);
}

