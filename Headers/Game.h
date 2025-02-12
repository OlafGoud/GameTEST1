
#pragma once
#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include "World.h"
#include "WorldObject.h"
#include <typeinfo>
#include <map>
#include <string>
#include <memory>


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
    static const unsigned int SCR_WIDTH = 1400;
    static const unsigned int SCR_HEIGHT = 800;
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
    int keysForAttachment[3] = {GLFW_KEY_E, GLFW_KEY_R, GLFW_KEY_T};
    std::vector<VehicleAttachment> attachmentList;
    std::map<std::string, std::shared_ptr<Vehicle>> vehicleMap;
    std::map<std::string, std::shared_ptr<VehicleAttachment>> vehicleAttachmentMap;
};

Game::Game(int height, int width, GLFWwindow* window) {
    Game::window = window;
    
      
    vehicleAttachmentMap.insert(std::pair<std::string, std::shared_ptr<VehicleAttachment>>("01klds", std::make_shared<FixedAttachment>("resources/objects/machines/seeder.obj", "01klds", glm::vec3(3.0f, 0.2, 5.0f), 0.0f, true, glm::vec3(0.8f, 0.8f, 0.8f))));
    vehicleMap.insert(std::pair<std::string, std::shared_ptr<Vehicle>>("00-00-00", std::make_shared<Tractor>("resources/objects/tractor/tractor1.obj", "00-00-00", glm::vec3(3.0f, 0.2f, 5.0f), 0.0f, true, glm::vec3(1.0f, 1.0f, 1.0f))));
    vehicleMap.insert(std::pair<std::string, std::shared_ptr<Vehicle>>("00-00-01", std::make_shared<Tractor>("resources/objects/tractor/tractor1.obj", "00-00-01", glm::vec3(-3.0f, 0.2f, -2.0f), 0.0f, true, glm::vec3(1.0f, 1.0f, 1.0f))));


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
        /**/
        for (auto it = vehicleMap.begin(); it != vehicleMap.end(); ++it) {
            it->second->render(objShader);
        }

        for (auto it = vehicleAttachmentMap.begin(); it != vehicleAttachmentMap.end(); ++it) {
            it->second->render(objShader);
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
    if (lastFrame - lastInteraction < 0.2) {
        return;
    }
    lastInteraction = lastFrame;
    for (auto it = vehicleMap.begin(); it != vehicleMap.end(); ++it) {
        if (player.visableToRender == false) {
            if (it->second->objectID == SelectedVehicleNumber) {
                SelectedVehicleNumber = "-1";
                std::cout << "vehicle unselected" << "\n";
                player.position = it->second->position + glm::vec3(0.4, 0, 0.4);
                camera.Target = player.position;
                camera.moveCamWithObject(glm::vec3(0.0f));
                player.visableToRender = true;
                return;
            }
        }

        if (glm::distance(it->second->position, player.position) < 0.5f) {
            SelectedVehicleNumber = it->second->objectID;
            std::cout << "vehicle selected" << "\n";
            camera.Target = it->second->position;
            camera.moveCamWithObject(glm::vec3(0.0f));
            player.visableToRender = false;
        }
    }

}


void Game::handleWASDMovement(bool forward, bool backward, bool turnLeft, bool turnRight) {

    if (SelectedVehicleNumber == "-1") {
        player.move(forward, backward, turnLeft, turnRight, deltaTime, camera);
        return;
    }
    Vehicle& vehicle = *Game::vehicleMap[SelectedVehicleNumber];
    for (int key : keysForAttachment) {
        if (glfwGetKey(window, key) == GLFW_PRESS) {
            if (lastFrame - lastInteraction < 0.5) {
                break;
            }
            if (vehicle.attachmentID == "-1") {
                break;
            }
            if(Game::vehicleAttachmentMap[vehicle.attachmentID]->derivedClassID == "EmptyAttachment") {
                break;
            }

            Game::vehicleAttachmentMap[vehicle.attachmentID]->buttonInteract(key);
        }
    }
    vehicle.addInput(forward, backward, turnLeft, turnRight, deltaTime, camera, objShader, *Game::vehicleAttachmentMap[vehicle.attachmentID]);
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
    
    // Update car movement    
    handleWASDMovement(forward, backward, turnLeft, turnRight);
}

