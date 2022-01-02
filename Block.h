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
	//int type;
	glm::vec3 position;
	glm::vec3 color;
	bool isSolid;

public:
	Block();
	Block(bool solid, glm::vec3 pos, glm::vec3 col);
};

