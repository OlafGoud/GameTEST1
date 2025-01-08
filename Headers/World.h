#pragma once

#ifndef WORLD_H
#define WORLD_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <vector>
#include <string>
#include <fstream>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "Model.h"
#include "Shader.h"
#include "Terrain.h"

struct ModelObject {
	Model model;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scaling;
	float angle;
};


class Scene {
public:
	Scene(Camera cam);
	~Scene();
	Scene() {}


	void loadScene(glm::mat4 view, glm::mat4 projection);
	void loadWorld();
	void loadObjects();
	glm::vec3 snapTo3DGrid(glm::vec3 position);
	void addComponent(glm::vec3 pos);
	Shader* getTerrainShader();
	Shader* getObjectShader();
	void loadPreview(int number, glm::vec3 pos);
	std::vector<std::vector<float>> getHeightMap() {
		return terrain.getHeightMap();
	}
	void loadCube(glm::mat4 view, glm::mat4 projection, float amount);
private:
	std::vector<std::vector<float>> worldHeihtMap;
	Shader objectShader;
	Shader terrainShader;
	glm::vec3 lightPos = glm::vec3(0.0f, 100.0f, 0.0f);
	std::vector<ModelObject> models;
	float celSize = 0.25;
	Camera cam1;
	int SCR_HEIGHT = 800;
	int SCR_WIDTH = 1400;
	GLint maxTessLevel;
	unsigned int terrainVAO, terrainVBO, terrainIBO;
	int numStrips, numTrisPerStrip;
	Terrain terrain = Terrain();
	std::vector<Model> previewModels;
	std::vector<std::vector<float>> terrainHeightPerPoint;
	std::vector<ModelObject> cube;
};
#endif