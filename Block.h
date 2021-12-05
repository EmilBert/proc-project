#pragma once

#include <string>
#include <vector>
#include"Mesh.h"
/*

	  y
	  |
	  |___x
	 /
	z
	   __________________
	---| Vertex indices |---

	   0_________ 1
	 / |	     /|
	2__|________3 |
	|  |		| |
	|  |		| |
	|  4________|_5
	| / 		| /
	6/__________7/

*/

class Block
{

public:
	static Vertex block_vertices[];
	static GLuint block_indices[];

	VAO VAO;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	Block();
	Block(glm::vec3 pos);
	void Draw(Shader& shader, Camera& camera);
};

