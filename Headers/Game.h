#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include "World.h"
#include "WorldObject.h"
#pragma once

class Game
{
public:
	Game(int height, int width, GLFWwindow* window);
	~Game();
	void render();
    void handleLeftClick(glm::vec3 worldPosition);
    void handleWASDMovement(bool forward, bool backward, bool turnLeft, bool turnRight);
    void processInput(GLFWwindow* window);
    void handleVehicleStepIn();

    //variables
    unsigned int VBO, cubeVAO;
    const unsigned int SCR_WIDTH = 1400;
    const unsigned int SCR_HEIGHT = 800;
    float deltaTime, lastInteraction = 0.0f;
    float lastFrame = 0.0f;
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f));
	Shader groundShader = Shader("resources/shaders/game.vs", "resources/shaders/game.fs");
	Shader objShader = Shader("resources/shaders/basic.vs", "resources/shaders/basic.fs");
    float vertices[288] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    World world = World();
    GLFWwindow* window;
    Player player = Player("resources/objects/human/humanred.obj", "Player", glm::vec3(2.0f, 0.2f, 3.0f), 0.0f, true, glm::vec3(0.5f, 0.5f, 0.5f), 2.0f);
    std::vector<Vehicle> vehicleList;
    std::string SelectedVehicleNumber = "-1";
    //std::vector<VehicleAttachment> attachmentList;
};

Game::Game(int height, int width, GLFWwindow* window) {
    Game::window = window;
    vehicleList.push_back(Tractor("resources/objects/tractor/tractor1.obj", "00-00-00", glm::vec3(3.0f, 0.2f, 5.0f), 0.0f, true, glm::vec3(1.0f, 1.0f, 1.0f)));
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    groundShader.use();
    groundShader.setVec3("lightColor", 0.0f, 100.0f, 0.0f);
    groundShader.setVec3("lightPos", 0, 20, 0);
    camera.Target = player.position;
    camera.moveCamWithObject(glm::vec3(0.0f));
}

Game::~Game()
{
}

void Game::render() {
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        groundShader.use();

        groundShader.setVec3("viewPos", camera.Position);
        groundShader.setMat4("projection", projection);
        groundShader.setMat4("view", view);
        world.render(groundShader, cubeVAO, camera.Position);

        for (auto vehicle : vehicleList) {
            if (vehicle.objectID == SelectedVehicleNumber) {
                vehicle.getNewPosition(deltaTime);
            }
            vehicle.render(objShader);
        }
        player.render(objShader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Game::handleLeftClick(glm::vec3 worldPosition) {
    world.changeGroundType(worldPosition);
}

void Game::handleVehicleStepIn() {
    if (lastFrame - lastInteraction < 0.3) {
        return;
    }
    lastInteraction = lastFrame;
    for (auto& vehicle : vehicleList) {
        if (vehicle.objectID == "-1") {
            continue;
        }
        if (player.visableToRender == false) {
            if (vehicle.objectID == SelectedVehicleNumber) {
                SelectedVehicleNumber = "-1";
                std::cout << "vehicle unselected" << "\n";                
                player.position = vehicle.position + glm::vec3(0.4, 0, 0.4);
                camera.Target = player.position;
                camera.moveCamWithObject(glm::vec3(0.0f));
                player.visableToRender = true;
                return;
            }
        }

        if (glm::distance(vehicle.position, player.position) < 0.5f) {
            SelectedVehicleNumber = vehicle.objectID;
            std::cout << "vehicle selected" << "\n";
            camera.Target = vehicle.position;
            camera.moveCamWithObject(glm::vec3(0.0f));
            player.visableToRender = false;
        }
    }
}


void Game::handleWASDMovement(bool forward, bool backward, bool turnLeft, bool turnRight) {
    for (auto& vehicle : vehicleList) {
        if (SelectedVehicleNumber == "-1") {
            player.move(forward, backward, turnLeft, turnRight, deltaTime, camera);
            return;
        }
        if (vehicle.objectID == SelectedVehicleNumber) {
            vehicle.addInput(forward, backward, turnLeft, turnRight, deltaTime);
        }
    }
}

void Game::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
    }
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        handleVehicleStepIn();
    }


    bool forward = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    bool backward = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    bool turnLeft = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    bool turnRight = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
    if (forward == true || backward == true || turnLeft == true || turnRight == true) {
        handleWASDMovement(forward, backward, turnLeft, turnRight);
    }
    // Update car movement
}
