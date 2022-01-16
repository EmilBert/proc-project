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
	
	Mesh chunkMesh;
	Mesh waterMesh;
	
	int worldRange;
	glm::vec3 position;
	
	std::vector<std::vector<std::vector<Block>>> &blocks;

public:
	Chunk(glm::vec3 pos, std::vector<std::vector<std::vector<Block>>>& data, int range);
	
	void GenerateMesh();
	void GenerateWaterMesh();
	void ExtractFace(Vertex vertices[], Block data, std::vector<Vertex>& verts, std::vector<GLuint>& inds);
	void Draw(Shader& shader, Camera& camera);
	void DrawWater(Shader& shader, Camera& camera);
};

