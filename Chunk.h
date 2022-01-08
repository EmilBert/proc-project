#pragma once

#include "Block.h"

const int WIDTH = 16;
const int HEIGHT = 128;

class Chunk
{
public:
	// Vertex Arrays
	static Vertex top_verts[];
	static Vertex bottom_verts[];

	static Vertex right_verts[];
	static Vertex left_verts[];

	static Vertex front_verts[];
	static Vertex back_verts[];

	// Index Array
	static GLuint face_inds[];

	GLuint index_depth = 0;
	
	Block blocks[WIDTH][HEIGHT][WIDTH];
	Mesh chunkMesh;
	Mesh waterMesh;
	glm::vec3 position;

public:
	Chunk(glm::vec3 pos);
	Chunk(glm::vec3 pos, std::vector<std::vector<std::vector<bool>>>& data);
	Chunk(glm::vec3 pos, std::vector<std::vector<std::vector<Block>>>& data);
	Chunk(Block data[WIDTH][HEIGHT][WIDTH]);


	void GenerateMesh();
	void GenerateWaterMesh();
	void ExtractFace(Vertex vertices[], Block data, std::vector<Vertex>& verts, std::vector<GLuint>& inds);
	void Draw(Shader& shader, Camera& camera);
	void DrawWater(Shader& shader, Camera& camera);
};

