#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <map>
#include "Shader.h"
#include "Chunk.h"
#include "stb_image.h"
#define WorldChunk_SIZE 16  // Each WorldChunk is 16x16
#define WORLD_HEIGHT 1  // Height in voxels

class World {
public:
    World();
    ~World();
    void render(Shader& shader, unsigned int& cubeVAO, glm::vec3 playerPos);
    void changeGroundType(glm::vec3 loc);
    unsigned int loadTexture(const char* path);

private:

    std::map<std::string, Chunk> worldChunks;
    unsigned int grayTexture = loadTexture("resources/textures/stone.png");
    std::vector<glm::vec2> getNearbyWorldChunks(glm::vec3 playerPos);

    std::string WorldChunkKey(glm::vec2 pos) {
        return std::to_string((int)pos.x) + "_" + std::to_string((int)pos.y);
    }
};

// ------------------------- Implementation -------------------------

World::World() {
    for (int x = -5; x < 5; x++) {
        for (int z = -5; z < 5; z++) {
            std::string key = WorldChunkKey(glm::vec2(x, z));
            worldChunks.emplace(key, Chunk(glm::vec2(x, z)));
        }
    }

}

World::~World() {}

std::vector<glm::vec2> World::getNearbyWorldChunks(glm::vec3 playerPos) {
    glm::vec2 WorldChunkCenter(
        std::round(playerPos.x / WorldChunk_SIZE),
        std::round(playerPos.z / WorldChunk_SIZE)
    );

    vector<glm::vec2> returnList;
    for (int i = -2; i < 2; i++) {
        for (int n = -2; n < 2; n++) {
            returnList.push_back(WorldChunkCenter + glm::vec2(i, n));
        }
    }


    return returnList;
}

void World::render(Shader& shader, unsigned int& cubeVAO, glm::vec3 playerPos) {
    
    auto WorldChunkPositions = getNearbyWorldChunks(playerPos);
    shader.setInt("inTexture", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, grayTexture);
    for (glm::vec2 WorldChunkPos : WorldChunkPositions) {
        std::string key = WorldChunkKey(WorldChunkPos);
        if (worldChunks.find(key) == worldChunks.end()) {
            continue;
        }

        Chunk& chunk = worldChunks[key];
        chunk.render(cubeVAO, shader);
        
    }
    shader.setVec3("groundColor", glm::vec3(1.0f, 1.0f, 1.0f));
}

void World::changeGroundType(glm::vec3 loc) {
    glm::vec2 WorldChunkPos(
        std::floor(loc.x / WorldChunk_SIZE),
        std::floor(loc.z / WorldChunk_SIZE)
    );
    std::string key = WorldChunkKey(WorldChunkPos);
    std::cout << "Ground changed at: " << loc.x << ", " << loc.y << ", " << loc.z << "\n";
    if (worldChunks.find(key) != worldChunks.end()) {
        Chunk& chunk = worldChunks[key];
        for (Voxel& voxel : chunk.voxelList) {
            if (glm::distance(voxel.position, loc) < 0.5f) {
                voxel.color = glm::vec3(0.39, 0.26, 0.03);
                std::cout << "Ground changed at: " << loc.x << ", " << loc.y << ", " << loc.z << "\n";
                return;
            }
        }
    }
}

unsigned int World::loadTexture(const char* path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);

    if (data) {
        GLenum format = (nrComponents == 4) ? GL_RGBA : GL_RGB;
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    }
    else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
