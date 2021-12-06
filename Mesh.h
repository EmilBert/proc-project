#pragma once

#include <string>
#include <vector>

#include "VAO.h"
#include "EBO.h"
#include "VBO.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture>textures;

	VAO VAO;
	Mesh();
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
	void AddToMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);

	void Draw(Shader& shader, Camera& camera);
};

