#pragma once
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

struct Voxel {
	glm::vec3 position;
	glm::vec3 color;
};


struct StaticObject
{
	Model model;
};


class Chunk
{
public:
	Chunk(glm::vec2 chunkPosition);
	~Chunk();
	Chunk() {}
	void render(unsigned int VBO, Shader& shader);
	const int size = 16;
	std::vector<Voxel> voxelList;

private:
	std::vector<StaticObject> staticObjectList;
	glm::vec2 chunkPosition;
};

Chunk::Chunk(glm::vec2 chunkPosition)
{
	Chunk::chunkPosition = chunkPosition;
	for (float x = 0; x < size; x += 0.5) {
		for (float z = 0; z < size; z += 0.5) {
			voxelList.push_back({ glm::vec3(x + (size * chunkPosition.x), 0.0f, z + (size * chunkPosition.y)), glm::vec3(0.13, 0.72, 0.29)});
		}
	}
}

Chunk::~Chunk() {

}

void Chunk::render(unsigned int cubeVAO, Shader& shader) {
	for (auto& voxel : voxelList) {

		shader.setVec3("groundColor", voxel.color);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, voxel.position);
		model = glm::scale(model, glm::vec3(0.5f));
		shader.setMat4("model", model);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

}