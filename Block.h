#pragma once

#include <string>
#include <vector>
#include"Mesh.h"

const int WIDTH = 16;
const int HEIGHT = 128;

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
	glm::vec3 position	= glm::vec3(0,0,0);
	glm::vec3 color		= glm::vec3(0,0,0);
	bool isSolid		= false;
	bool isTransparent	= false;

public:
	Block(){};
	Block(bool solid, glm::vec3 pos, glm::vec3 col) : isSolid(solid), isTransparent(false), position(pos), color(col) {}
};

