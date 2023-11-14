#pragma once
#include "Block.h"
#include "GeneratedNoise.h"
#include<thread>
#include<map>

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
	
	bool regenMesh = true;
	Mesh chunkMesh;
	Mesh waterMesh;

	bool building = false;
	bool setMesh = false;

	std::vector<Vertex> verts;
	std::vector<GLuint> inds;
	
	glm::vec2 chunkPosition;
	glm::vec3 position;
	Block blocks[WIDTH][HEIGHT][WIDTH];

public:
	Chunk();
	Chunk(glm::vec2 cp, GeneratedNoise noise);
	~Chunk();
	void Generate();
	void SetMesh();
	void GenerateWaterMesh();
	static void ExtractFace(Vertex vertices[], Block data, std::vector<Vertex>& verts, std::vector<GLuint>& inds, GLuint &index_depth);
	void Draw(Shader& shader, Camera& camera);
	void DrawWater(Shader& shader, Camera& camera);
};

