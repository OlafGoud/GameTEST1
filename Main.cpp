#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "Headers/Shader.h"
#include "Headers/Camera.h"
#include "Headers/Model.h"
#include "Headers/World.h"


#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
int setSettings();
glm::vec3 getWorldPosition();
// settings
const unsigned int SCR_WIDTH = 1400;
const unsigned int SCR_HEIGHT = 800;
Scene world;
// camera
Camera camera(glm::vec3(0.0f, 20.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
GLFWwindow* window;
// lighting
int number = 0;



int main()
{
    if (setSettings() == -1) {
        return -1;
    }
    

    world = Scene(camera);
    Shader* terrainShader = world.getTerrainShader();
    Shader* objectShader = world.getObjectShader();

    Shader lightShader("resources/shaders/rotCubeLight.vs", "resources/shaders/rotCubeLight.fs");

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
        (*terrainShader).use();
        (*terrainShader).setMat4("projection", projection);
        (*terrainShader).setMat4("view", view);
        (*objectShader).use();
        (*objectShader).setMat4("projection", projection);
        (*objectShader).setMat4("view", view);

        
        // render the loaded model
        world.loadScene(view, projection);

        if (!(number == 0)) {
            world.loadPreview(number, getWorldPosition());
        }
        
        //world.loadCube(view, projection, 100 * currentFrame);

        lightShader.use();
        lightShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        lightShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightShader.setVec3("lightPos", glm::vec3(3, 10, 3));
        lightShader.setVec3("viewPos", camera.Position);
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 3.0f, 1.0f));
        model = glm::scale(model, glm::vec3(2.0f)); // a smaller cube
        model = glm::rotate(model, glm::radians(100 * currentFrame), glm::vec3(0.0f, 1.0f, 0.0f));

        lightShader.setMat4("model", model);
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);



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
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            camera.ProcessKeyboard(FORWARD, deltaTime * 3);
        }
        else {
            camera.ProcessKeyboard(FORWARD, deltaTime);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            camera.ProcessKeyboard(BACKWARD, deltaTime * 3);
        }
        else {
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            camera.ProcessKeyboard(LEFT, deltaTime * 3);
        }
        else {
            camera.ProcessKeyboard(LEFT, deltaTime);
        }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            camera.ProcessKeyboard(RIGHT, deltaTime * 3);
        }
        else {
            camera.ProcessKeyboard(RIGHT, deltaTime);
        }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        number = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        number = 0;
    }
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
        camera.ProcessMouseMovement(xoffset, yoffset);
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



// Function to unproject screen space coordinates to world coordinates
glm::vec3 unProjectMousePosition(float winX, float winY, float winZ,
    const glm::mat4& projectionMatrix,
    const glm::mat4& viewMatrix,
    const glm::ivec4& viewport)
{
    // Convert screen space to NDC
    float ndcX = (winX - viewport.x) / viewport.z * 2.0f - 1.0f;
    float ndcY = (winY - viewport.y) / viewport.w * 2.0f - 1.0f;
    float ndcZ = 2.0f * winZ - 1.0f;

    // Combine projection and view matrices
    glm::mat4 combined = projectionMatrix * viewMatrix;

    // Inverse of the combined matrix
    glm::mat4 inverseCombined = glm::inverse(combined);

    // Unproject the normalized device coordinates to world space
    glm::vec4 ndcPos(ndcX, ndcY, ndcZ, 1.0f);
    glm::vec4 worldPos = inverseCombined * ndcPos;

    // Convert to 3D world position
    glm::vec3 worldPos3D = glm::vec3(worldPos) / worldPos.w; // Homogeneous division
    return worldPos3D;
}

// Function to get the intersection point with the ground plane (y = 0)
glm::vec3 placeObjectOnGround(float winX, float winY, float winZ,
    const glm::mat4& projectionMatrix,
    const glm::mat4& viewMatrix,
    const glm::ivec4& viewport)
{
    // Unproject the mouse position to world space
    glm::vec3 worldPos = unProjectMousePosition(winX, winY, winZ, projectionMatrix, viewMatrix, viewport);

    // Assume the ground is at y = 0, so find the intersection point with the plane y = 0
    if (worldPos.y != 0.0f) {
        // Find the ratio of how far along the ray the intersection occurs (t)
        float t = -worldPos.y / worldPos.z;

        // Calculate the intersection point with the ground plane (y = 0)
        glm::vec3 intersectionPoint = worldPos + t * (worldPos - glm::vec3(worldPos.x, 0.0f, worldPos.z));
        return intersectionPoint;
    }

    // If the y position is already on the ground, return the current position
    return worldPos;
}

glm::vec3 getWorldPosition() {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    /*
    float depth;
    glReadPixels(mouseX, SCR_HEIGHT - (mouseY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glm::vec4 clipCoords = glm::vec4((((2.0f * (mouseX)) / SCR_WIDTH) - 1.0f), (1.0f - (2.0f * (mouseY)) / SCR_HEIGHT), depth * 2.0f - 1.0f, 1.0f);
    glm::mat4 projectionMatrix = camera.GetProjectionMatrix((float)SCR_WIDTH / (float)SCR_HEIGHT);
    glm::vec4 viewCoords = glm::inverse(projectionMatrix) * clipCoords;
    viewCoords /= viewCoords.w;

    glm::vec4 worldCoords = glm::inverse(camera.GetViewMatrix()) * viewCoords;
    glm::vec3 worldPosition = glm::vec3(worldCoords);
    
    return worldPosition;
    */


    // Step 1: Read depth at mouse position
    float depth;
    glReadPixels(mouseX, SCR_HEIGHT - mouseY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

    // Step 2: Convert screen-space coordinates to clip-space (NDC)
    glm::vec4 clipCoords = glm::vec4(
        (((2.0f * (float)mouseX) / (float)SCR_WIDTH) - 1.0f), // x
        (1.0f - (2.0f * (float)mouseY) / (float)SCR_HEIGHT), // y
        depth * 2.0f - 1.0f, // z (depth)
        1.0f
    );

    // Step 3: Get the projection matrix from the camera
    glm::mat4 projectionMatrix = camera.GetProjectionMatrix((float)SCR_WIDTH / (float)SCR_HEIGHT);

    // Step 4: Unproject to view space (inverse of the projection matrix)
    glm::vec4 viewCoords = glm::inverse(projectionMatrix) * clipCoords;
    viewCoords /= viewCoords.w;  // Divide by w to get normalized coordinates in view space

    // Step 5: Convert from view space to world space
    glm::vec4 worldCoords = glm::inverse(camera.GetViewMatrix()) * viewCoords;

    // Step 6: Convert the world position to a 3D vector
    glm::vec3 worldPosition = glm::vec3(worldCoords);

    // Step 7: Ensure the y value stays at the fixed position (e.g., y = 0)
    worldPosition.y = world.getHeightMap().at(worldPosition.x).at(worldPosition.z); // Set the world position to the fixed Y value (e.g., ground plane)
    cout << worldPosition.y << "\n";
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
    if (worldPosition.x < 50 && worldPosition.x > 20 && worldPosition.z < 50 && worldPosition.z > 20) {
        world.addComponent(worldPosition);
    }
    std::cout << "pos: " << worldPosition.x << ", " << worldPosition.y << ", " << worldPosition.z << "\n";
    
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
