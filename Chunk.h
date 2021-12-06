#pragma once

#include "Block.h"

const int WIDTH = 32;
const int HEIGHT = 32;

class Chunk
{
public:
	std::vector<Vertex> verts;
	std::vector<GLuint> inds;

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

public:
	Chunk();
	Chunk(Block data[WIDTH][HEIGHT][WIDTH]);

	void GenerateMesh();
	void ExtractFace(Vertex vertices[], glm::vec3 pos);
	void Draw(Shader& shader, Camera& camera);
};

