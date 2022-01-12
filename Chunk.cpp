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




Chunk::Chunk(glm::vec3 pos, std::vector<std::vector<std::vector<Block>>>& data, int range) : blocks(data), worldRange(range) {
	
	position = { WIDTH * pos.x, pos.y, WIDTH * pos.z };

	GenerateMesh();
}

//vertices = std::vector<Vertex>(block_vertices, block_vertices + sizeof(block_vertices) / sizeof(Vertex));
//indices = std::vector<GLuint>(block_indices, block_indices + sizeof(block_indices) / sizeof(GLuint));

// Extract the given face and put its
// vertices and indices in their respective vector
void Chunk::ExtractFace(Vertex vertices[], Block data ,std::vector<Vertex> &verts, std::vector<GLuint> &inds)
{
	glm::mat4 model = glm::mat4(1.0f);


	model = glm::translate(model, -position + glm::vec3(data.position.x, data.position.y, data.position.z));

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

	int x_start = position.x;
	int z_start = position.z;

	index_depth = 0;
	for (size_t y = 0; y < HEIGHT; y++)
	for (size_t x = x_start; x < x_start + WIDTH; x++)
	for (size_t z = z_start; z < z_start + WIDTH; z++)
	{

		Block *current = &blocks[x][y][z];
		
		/*std::cout << "x:" << x << std::endl;
		std::cout << "y:" << y<< std::endl;
		std::cout << "z:" << z <<std::endl;*/

		// Is this Block solid?
		if (current->isSolid) 
		{
			//Check right and left
			if (x_start < 1 || !blocks[x - 1][y][z].isSolid) {
				ExtractFace(left_verts, blocks[x][y][z], verts, inds);
			}
			if (x >  worldRange * WIDTH-2 || !blocks[x + 1][y][z].isSolid)	{
				ExtractFace(right_verts, blocks[x][y][z], verts, inds);
			}
			//Check top and bottom
			if (y < 1 || !blocks[x][y - 1][z].isSolid){
				ExtractFace(bottom_verts, blocks[x][y][z], verts, inds);
			}
			if (y > HEIGHT-2 || !blocks[x][y + 1][z].isSolid)	{
				ExtractFace(top_verts, blocks[x][y][z], verts, inds);
			}
			//Check front and back
			if (z_start < 1 || !blocks[x][y][z - 1].isSolid) {
				ExtractFace(back_verts, blocks[x][y][z], verts, inds);
			}
			if (z > worldRange * WIDTH - 2 || !blocks[x][y][z + 1].isSolid) {
				ExtractFace(front_verts, blocks[x][y][z], verts, inds);
			}
		}
	}

	chunkMesh = Mesh(verts, inds, position);
	GenerateWaterMesh();
}

void Chunk::GenerateWaterMesh()
{	

	std::vector<Vertex> verts;
	std::vector<GLuint> inds;

	int x_start = position.x;
	int z_start = position.z;

	index_depth = 0;
	for (size_t y = 0; y < HEIGHT; y++)
	for (size_t x = x_start; x < x_start + WIDTH; x++)
	for (size_t z = z_start; z < z_start + WIDTH; z++)
	{
		// Is this Block transparent?
		if (blocks[x][y][z].isTransparent)
		{
			//Check right and left
			if (x < 1) {
				ExtractFace(left_verts, blocks[x][y][z], verts, inds);
			}
			if (x > worldRange* WIDTH - 2) {
				ExtractFace(right_verts, blocks[x][y][z], verts, inds);
			}
			//Check top and bottom
			/*if (y < 1 || !blocks[x][y - 1][z].isTransparent || !blocks[x][y - 1][z].isSolid) {
				ExtractFace(bottom_verts, blocks[x][y][z], verts, inds);
			}*/
			if (y > HEIGHT - 2 || !blocks[x][y + 1][z].isTransparent) {
				ExtractFace(top_verts, blocks[x][y][z], verts, inds);
			}
			//Check front and back
			if (z < 1 ) {
				ExtractFace(back_verts, blocks[x][y][z], verts, inds);
			}
			if (z > worldRange* WIDTH - 2 ) {
				ExtractFace(front_verts, blocks[x][y][z], verts, inds);
			}
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




