#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include "World.h"

#pragma once

struct WorldObjects
{
	Model model;
	glm::vec3 location;
	float rotation;
	int number;
    bool active;
};

class Game
{
public:
	Game(int height, int width, GLFWwindow* window);
	~Game();
	void render();
    void handleLeftClick(glm::vec3 worldPosition);
    void moveCar(WorldObjects& car, bool forward, bool backward, bool turnLeft, bool turnRight, float deltaTime, float speed);
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
    //World world;
	Shader groundShader = Shader("resources/shaders/game.vs", "resources/shaders/game.fs");
	Shader objShader = Shader("resources/shaders/basic.vs", "resources/shaders/basic.fs");
	std::vector<WorldObjects> worldObjectList;
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
    int selectedObjectNumber = -1;
    WorldObjects player = { Model("resources/objects/human/humanred.obj"), glm::vec3(0.0f, 0.2f, 0.0f), 0, 0, true};

};

Game::Game(int height, int width, GLFWwindow* window) {
    Game::window = window;
    worldObjectList.push_back({ Model("resources/objects/tractor/tractor1.obj") , glm::vec3(3.0f, 0.2f, 0.0f), 40, 1, true });
    worldObjectList.push_back({ Model("resources/objects/tractor/tractor1.obj") , glm::vec3(10.0f, 0.2f, 0.0f), 30, 2, true });
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
    camera.Target = player.location;
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

        for (auto vehicleModel : worldObjectList) {
            if (!vehicleModel.active) {
                continue;
            }

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, vehicleModel.location);
            model = glm::rotate(model, glm::radians(vehicleModel.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            objShader.setMat4("model", model);
            vehicleModel.model.Draw(objShader);
        }
        if (player.active) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, player.location);
            model = glm::rotate(model, glm::radians(player.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
            objShader.setMat4("model", model);
            player.model.Draw(objShader);
        }
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
        std::cout << lastFrame - lastInteraction << "<< last\n";
        return;
    }
    lastInteraction = lastFrame;
    for (auto& model : worldObjectList) {
        if (model.number == -1) {
            continue;
        }
        if (player.active == false) {
            if (model.number == selectedObjectNumber) {
                selectedObjectNumber = -1;
                std::cout << "vehicle unselected" << "\n";                
                player.location = model.location + glm::vec3(0.4, 0, 0.4);
                camera.Target = player.location;
                camera.moveCamWithObject(glm::vec3(0.0f));
                player.active = true;
                return;
            }
        }

        if ((model.location.x + 0.5f > player.location.x && model.location.x - 0.5f < player.location.x) && (model.location.z + 0.5f > player.location.z && model.location.z - 0.5f < player.location.z)) {
            selectedObjectNumber = model.number;
            std::cout << "vehicle selected" << "\n";
            camera.Target = model.location;
            camera.moveCamWithObject(glm::vec3(0.0f));
            player.active = false;
        }
    }
}


void Game::moveCar(WorldObjects& car, bool forward, bool backward, bool turnLeft, bool turnRight, float deltaTime, float speed) {
    // Update rotation for turning (Y-axis rotation)
    if (turnLeft) {
        car.rotation += 90.0f * deltaTime; // Counterclockwise rotation
    }
    if (turnRight) {
        car.rotation -= 90.0f * deltaTime; // Clockwise rotation
    }

    // Normalize the rotation angle to keep it between 0 and 360 degrees
    if (car.rotation > 360.0f) car.rotation -= 360.0f;
    if (car.rotation < 0.0f) car.rotation += 360.0f;

    // Calculate the forward direction based on the car's rotation (ignore the Y-axis for movement)
    glm::vec3 forwardDirection;
    forwardDirection.x = -cos(glm::radians(car.rotation - 90));  // X movement based on rotation
    forwardDirection.z = sin(glm::radians(car.rotation - 90));  // Z movement based on rotation
    forwardDirection.y = 0.0f;  // Ensure no vertical movement

    forwardDirection = glm::normalize(forwardDirection); // Normalize to keep the speed consistent

    // Update the position for forward/backward movement
    if (forward) {
        car.location += forwardDirection * speed * deltaTime; // Move forward along the direction
        camera.moveCamWithObject(forwardDirection * speed * deltaTime); // Move backward (opposite direction)
    }
    if (backward) {
        car.location -= forwardDirection * speed * deltaTime; // Move backward (opposite direction)
        camera.moveCamWithObject(-(forwardDirection * speed * deltaTime)); // Move backward (opposite direction)
    }

    // Debugging output to verify the movement and rotation
    std::cout << "Rotation: " << car.rotation << " degrees\n";
    std::cout << "Location: x: " << car.location.x << ", y: " << car.location.y << ", z: " << car.location.z << "\n";
}

void Game::handleWASDMovement(bool forward, bool backward, bool turnLeft, bool turnRight) {
    for (auto& model : worldObjectList) {
        if (selectedObjectNumber == -1) {
            Game::moveCar(player, forward, backward, turnLeft, turnRight, deltaTime, 2.0);
            return;
        }
        if (model.number == selectedObjectNumber) {
            Game::moveCar(model, forward, backward, turnLeft, turnRight, deltaTime, 5.0f);
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
