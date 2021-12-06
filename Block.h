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
	glm::vec3 position;
	bool isSolid;

public:
	Block();
	Block(bool solid, glm::vec3 pos);
};

