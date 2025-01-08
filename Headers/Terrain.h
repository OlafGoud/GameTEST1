#pragma once
#ifndef TERRAIN_H
#define TERRAIN_H

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
#include "Camera.h"


class Terrain
{
public:
	Terrain(const char* mapStr);
    Terrain() {};
	~Terrain();

	void loadTerrain(const char* mapLocation);
    void renderTerrain(Shader &shader, Camera& cam);
    unsigned int loadTexture(char const* path);
    std::vector<float> getVertices() {
        return vertices;
    }
    std::vector<unsigned int> getIndices() {
        return indices;
    }
    int getWidth() {
        return width;
    }
    int getLength() {
        return height;
    }
    std::vector<std::vector<float>> getHeightMap() {
        return heightMap;
    }

private:
    float gridSize = 50;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO, VBO, EBO;
    int width, height;
    unsigned int grassTexture;
    unsigned int rockTexture;
    
    std::vector<std::vector<float>> heightMap;
};

#endif