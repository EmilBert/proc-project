#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>


struct Vertex {
	glm::vec3 vertices;
	glm::vec3 indices;
	glm::vec3 color;
	glm::vec2 UVcoord;
};

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(std::vector<Vertex>& vertices);

	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
};
