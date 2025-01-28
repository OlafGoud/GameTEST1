#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "Headers/Shader.h"
#include "Headers/Camera.h"
#include "Headers/Model.h"
#include "Headers/World.h"
#include "Headers/Game.h"
#include "Headers/stb_image.h"
#include <iostream>


struct WorldObjects
{
    Model model;
    glm::vec3 location;
    float rotation;
    int number;
};

int selectedObjectNumber = -1;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
int setSettings();
glm::vec3 getWorldPosition();
void moveCar(WorldObjects& car, bool forward, bool backward, bool turnLeft, bool turnRight, float deltaTime, float speed);
// settings
const unsigned int SCR_WIDTH = 1400;
const unsigned int SCR_HEIGHT = 800;
// camera
Camera camera(glm::vec3(0.0f, 10.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
GLFWwindow* window;
// lighting
int number = 0;
std::vector<World> worldInst;
std::vector<WorldObjects> modelList;

int main()
{
    if (setSettings() == -1) {
        return -1;
    }

    Game game = Game();

    worldInst.push_back(World());


    Shader groundShader("resources/shaders/game.vs", "resources/shaders/game.fs");
    Shader objShader("resources/shaders/basic.vs", "resources/shaders/basic.fs");
    modelList.push_back({ Model("resources/objects/cube.obj") , glm::vec3(1000000.0f, 1000000.0f, 1000000.0f), 0, -1});
    modelList.push_back({ Model("resources/objects/tractor/tractor1.obj") , glm::vec3(0.0f, 0.2f, 0.0f), 40, 1 });
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    groundShader.use();
    groundShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    groundShader.setVec3("lightPos", 0, 20, 0);
    



    // render loop
    // -----------
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
        worldInst[0].render(groundShader, cubeVAO);
        
        for (auto vehicleModel : modelList) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, vehicleModel.location);
            model = glm::rotate(model, glm::radians(vehicleModel.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            objShader.setMat4("model", model);
            vehicleModel.model.Draw(objShader);
        }

        


        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        number = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        number = 0;
    }

    bool forward = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    bool backward = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    bool turnLeft = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    bool turnRight = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
    if (forward == true || backward == true || turnLeft == true || turnRight == true) {
        for (auto& model : modelList) {
            if (model.number == selectedObjectNumber) {
                moveCar(model, forward, backward, turnLeft, turnRight, deltaTime, 5.0f);
            }
        }
    }
    // Update car movement
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    // Check if the left mouse button is pressed
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        // Calculate the offset from the last position
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        // Update the last known position for the next frame
        lastX = xpos;
        lastY = ypos;

        // Apply the offset to the camera's movement logic
        camera.processCameraMovement(xoffset, yoffset);
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        // Update the last known position for the next frame
        lastX = xpos;
        lastY = ypos;

        // Apply the offset to the camera's movement logic
        camera.prosessWorldMovement(xoffset, yoffset);
    }
    else {
        // Reset the last known position when the mouse button is released
        lastX = xpos;
        lastY = ypos;
    }

    
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


glm::vec3 getWorldPosition() {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    
    float depth;
    glReadPixels(mouseX, SCR_HEIGHT - (mouseY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glm::vec4 clipCoords = glm::vec4((((2.0f * (mouseX)) / SCR_WIDTH) - 1.0f), (1.0f - (2.0f * (mouseY)) / SCR_HEIGHT), depth * 2.0f - 1.0f, 1.0f);
    glm::mat4 projectionMatrix = camera.GetProjectionMatrix((float)SCR_WIDTH / (float)SCR_HEIGHT);
    glm::vec4 viewCoords = glm::inverse(projectionMatrix) * clipCoords;
    viewCoords /= viewCoords.w;

    glm::vec4 worldCoords = glm::inverse(camera.GetViewMatrix()) * viewCoords;
    glm::vec3 worldPosition = glm::vec3(worldCoords);
    
    return worldPosition;
}

void mouseClickCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        return;
    }
    if (action == GLFW_HAT_UP) {
        return;
    }

    glm::vec3 worldPosition = getWorldPosition();
    for (auto& model : modelList) {
        if (model.number == -1) {
            continue;
        }

        if ((model.location.x + 0.5f > worldPosition.x && model.location.x - 0.5f < worldPosition.x) && (model.location.z + 0.5f > worldPosition.z && model.location.z - 0.5f < worldPosition.z)) {
            if (model.number == selectedObjectNumber) {
                selectedObjectNumber = -1;
                std::cout << "vehicle unselected" << "\n";

            }
            else {
                selectedObjectNumber = model.number;
                std::cout << "vehicle selected" << "\n";
            }
            
        }
    }


    worldInst[0].changeGroundType(worldPosition);
    
}

int setSettings() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, 0);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "School Game", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouseClickCallback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    return 0;
}


void moveCar(WorldObjects& car, bool forward, bool backward, bool turnLeft, bool turnRight, float deltaTime, float speed) {
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
    forwardDirection.x = -cos(glm::radians(car.rotation -90));  // X movement based on rotation
    forwardDirection.z = sin(glm::radians(car.rotation -90));  // Z movement based on rotation
    forwardDirection.y = 0.0f;  // Ensure no vertical movement

    forwardDirection = glm::normalize(forwardDirection); // Normalize to keep the speed consistent

    // Update the position for forward/backward movement
    if (forward) {
        car.location += forwardDirection * speed * deltaTime; // Move forward along the direction
    }
    if (backward) {
        car.location -= forwardDirection * speed * deltaTime; // Move backward (opposite direction)
    }

    // Debugging output to verify the movement and rotation
    std::cout << "Rotation: " << car.rotation << " degrees\n";
    std::cout << "Location: x: " << car.location.x << ", y: " << car.location.y << ", z: " << car.location.z << "\n";
}

