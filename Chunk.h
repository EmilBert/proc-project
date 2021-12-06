#pragma once

#include "Block.h"

const int WIDTH = 16;
const int HEIGHT = 64;

class Chunk
{

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

	Block blocks[WIDTH][HEIGHT][WIDTH];
	Mesh chunkMesh;

	Chunk();
	Chunk(Block data[WIDTH][HEIGHT][WIDTH]);

	void GenerateMesh();
	void ExtractFace(Vertex vertices[]);
	void Draw(Shader& shader, Camera& camera);
};

