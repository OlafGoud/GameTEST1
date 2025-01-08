#include "../Terrain.h"


Terrain::Terrain(const char* mapStr)
{
    grassTexture = loadTexture("resources/textures/green.png");
    rockTexture = loadTexture("resources/textures/stone.png");
    loadTerrain(mapStr);
}

Terrain::~Terrain() {}



void Terrain::loadTerrain(const char* mapLocation) {
    int nrChannels;
    unsigned char* data = stbi_load(mapLocation, &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load heightmap at: " << mapLocation << std::endl;
        return;
    }

    std::cout << "Loaded heightmap: " << width << "x" << height << " with " << nrChannels << " channels." << std::endl;

    float yScale = 64.0f / 255.0f, yShift = 8.0f;

    std::vector<glm::vec3> vertexPositions(width * height, glm::vec3(0.0f));
    std::vector<glm::vec3> normals(width * height, glm::vec3(0.0f));
    std::vector<glm::vec2> texCoords(width * height, glm::vec2(0.0f));
    float texScale = 300.0f;         // Texture scaling factor

    // Generate vertices and texture coordinates
    for (int z = 0; z < height; ++z) {
        std::vector<float> subMap;
        for (int x = 0; x < width; ++x) {
            // Calculate vertex index
            int index = z * width + x;

            // Calculate height based on the grayscale value of the heightmap
            unsigned char pixelValue = data[(z * width + x) * nrChannels];
            float y = pixelValue * yScale - yShift;
            subMap.push_back(y);
            // Store vertex position
            vertexPositions[index] = glm::vec3(x, y, z);

            // Store texture coordinates
            texCoords[index] = glm::vec2((float)x / (width - 1), (float)z / (height - 1)) * texScale;
        }
        heightMap.push_back(subMap);
    }

    // Generate normals by calculating cross products for triangles
    for (int z = 0; z < height - 1; ++z) {
        for (int x = 0; x < width - 1; ++x) {
            // Calculate indices for a quad (two triangles)
            int topLeft = z * width + x;
            int topRight = topLeft + 1;
            int bottomLeft = (z + 1) * width + x;
            int bottomRight = bottomLeft + 1;

            // Triangle 1 (top-left, bottom-left, top-right)
            glm::vec3 normal1 = glm::normalize(glm::cross(
                vertexPositions[bottomLeft] - vertexPositions[topLeft],
                vertexPositions[topRight] - vertexPositions[topLeft]));
            normals[topLeft] += normal1;
            normals[bottomLeft] += normal1;
            normals[topRight] += normal1;

            // Triangle 2 (top-right, bottom-left, bottom-right)
            glm::vec3 normal2 = glm::normalize(glm::cross(
                vertexPositions[bottomRight] - vertexPositions[bottomLeft],
                vertexPositions[topRight] - vertexPositions[bottomLeft]));
            normals[topRight] += normal2;
            normals[bottomLeft] += normal2;
            normals[bottomRight] += normal2;
        }
    }

    // Normalize all normals
    for (int i = 0; i < normals.size(); ++i) {
        normals[i] = glm::normalize(normals[i]);
    }

    // Generate final vertex data (interleaved position, texture, normal)
    vertices.clear();
    for (int i = 0; i < width * height; ++i) {
        vertices.push_back(vertexPositions[i].x);
        vertices.push_back(vertexPositions[i].y);
        vertices.push_back(vertexPositions[i].z);
        vertices.push_back(texCoords[i].x);
        vertices.push_back(texCoords[i].y);
        vertices.push_back(normals[i].x);
        vertices.push_back(normals[i].y);
        vertices.push_back(normals[i].z);
    }

    // Generate indices for rendering
    for (int z = 0; z < height - 1; ++z) {
        for (int x = 0; x < width - 1; ++x) {
            int topLeft = z * width + x;
            int topRight = topLeft + 1;
            int bottomLeft = (z + 1) * width + x;
            int bottomRight = bottomLeft + 1;

            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);

            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }

    // Free the heightmap data
    stbi_image_free(data);

    // OpenGL buffer setup
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // Position
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Texture coords
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float))); // Normals
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}


void Terrain::renderTerrain(Shader& shader, Camera& cam) {
    shader.setInt("grassTexture", 0);
    shader.setInt("rockTexture", 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, grassTexture);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, rockTexture);

    shader.setVec3("lightPos", glm::vec3(0.0f, 100.0f, 0.0f));
    shader.setVec3("viewPos", cam.Position);
    shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.1f, 0.5f, 0.1));	// it's a bit too big for our scene, so scale it down
    shader.setMat4("model", model);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}


unsigned int Terrain::loadTexture(char const* path)
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