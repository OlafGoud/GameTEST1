#pragma once
#include <iostream>
#include <vector>
#include <map>

enum GroundType
{
	SOIL1,
	SOIL2,
	STONE,
	GRASS
};

struct Land
{
	GroundType type;
	glm::vec3 position;
};


class World
{
public:
	World();
	~World();
	void render(Shader& shader, unsigned int& cubeVAO);
	unsigned int loadTexture(char const* path);
	void changeGroundType(glm::vec3 loc);
private:
	std::vector<Land> worldMap;
	std::map<GroundType, unsigned int> textureMap;
};

World::World()
{
	std::cout << "adsf";
	for (float i = -10; i < 10; i += 0.5) {
		for (float n = -10; n < 10; n += 0.5) {
			worldMap.push_back({GRASS, glm::vec3(i, 0.0f, n)});
			cout << n << "\n";
			cout << i << "\n";
		}
	}
	textureMap[SOIL1] = loadTexture("resources/textures/soil1.png");
	textureMap[STONE] = loadTexture("resources/textures/stone.png");
	textureMap[SOIL2] = loadTexture("resources/textures/soil2.png");
	textureMap[GRASS] = loadTexture("resources/textures/grass.png");
	std::cout << "adsf";
}

World::~World()
{
}

void World::render(Shader& shader, unsigned int& cubeVAO) {
	for (auto land : worldMap) {
		unsigned int texture = textureMap[land.type];
		shader.setInt("inTexture", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, land.position);
		model = glm::scale(model, glm::vec3(0.5f)); // a smaller cube

		shader.setMat4("model", model);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

unsigned int World::loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

void World::changeGroundType(glm::vec3 loc) {
	loc.x = std::round(loc.x * 2) / 2;
	loc.y = std::round(loc.y * 2) / 2;
	loc.z = std::round(loc.z * 2) / 2;
	std::cout << "pos: " << loc.x << ", " << loc.y << ", " << loc.z << "\n";
	for (Land& land : worldMap) {
		if (land.position == loc) {
			land.type = SOIL1;
			std::cout << "foind" << "\n";
		}
	}
}
