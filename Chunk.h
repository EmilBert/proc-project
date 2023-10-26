#pragma once
#include "Block.h"
#include "GeneratedNoise.h"

class Chunk
{
public:
	
	// For traversal
	int distance = 0;
	Chunk* left = nullptr;
	Chunk* right = nullptr;
	Chunk* front = nullptr;
	Chunk* back = nullptr;

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
	
	bool regenMesh = true;
	Mesh chunkMesh;
	Mesh waterMesh;

	std::vector<Vertex> verts;
	std::vector<GLuint> inds;
	
	glm::vec2 chunkPosition;
	glm::vec3 position;
	Block blocks[WIDTH][HEIGHT][WIDTH];

public:
	Chunk();
	Chunk(int chunkCoord_x, int chunkCoord_z, GeneratedNoise noise);

	void GenerateMesh(Chunk* leftChunk, Chunk* rightChunk, Chunk* infrontChunk, Chunk* behindChunk);
	void GenerateWaterMesh();
	void ExtractFace(Vertex vertices[], Block data, std::vector<Vertex>& verts, std::vector<GLuint>& inds);
	void Draw(Shader& shader, Camera& camera);
	void DrawWater(Shader& shader, Camera& camera);
};

