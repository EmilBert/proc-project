#pragma once

#include <string>
#include <vector>

#include "VAO.h"
#include "EBO.h"
#include "VBO.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"

const float scale = 1.0f / 16.0f;

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture>textures;
	glm::vec3 position;
	
	VAO VAO;
	Mesh();
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, glm::vec3 pos);

	//void AddToMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
	void Draw(Shader& shader, Camera& camera);
};

