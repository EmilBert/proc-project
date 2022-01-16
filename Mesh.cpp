#include "Mesh.h"

Mesh::Mesh(){}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, glm::vec3 pos)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	position = pos;

	VAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO(vertices);
	// Generates Element Buffer Object and links it to indices
	EBO EBO(indices);

	// Links VBO attributes such as coordinates and colors to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	//VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera)
{
	shader.Activate();
	VAO.Bind();

	glm::mat4 model = glm::mat4(1.0f);
	float scale = 0.1;
	glm::mat4 scaleMat = glm::scale(glm::vec3(scale));
	model = glm::translate(model, scale*position);


	// Take care of the camera Matrix
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(scaleMat));

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
