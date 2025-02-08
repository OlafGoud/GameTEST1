#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "Headers/Camera.h"
#include "Headers/Game.h"
#include <iostream>



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
int setSettings();
glm::vec3 getWorldPosition();
// settings
const unsigned int SCR_WIDTH = 1400;
const unsigned int SCR_HEIGHT = 800;
// camera
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
// timing
GLFWwindow* window;

std::vector<Game> gameInst;

int main()
{
    if (setSettings() == -1) {
        return -1;
    }

    gameInst.push_back(Game(SCR_WIDTH, SCR_HEIGHT, window));

    gameInst[0].render();
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
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
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
        // Calculate the offset from the last position
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        // Update the last known position for the next frame
        lastX = xpos;
        lastY = ypos;

        // Apply the offset to the camera's movement logic
        gameInst[0].camera.processCameraMovement(xoffset, yoffset);
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
    gameInst[0].camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


glm::vec3 getWorldPosition() {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    
    float depth;
    glReadPixels(mouseX, SCR_HEIGHT - (mouseY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glm::vec4 clipCoords = glm::vec4((((2.0f * (mouseX)) / SCR_WIDTH) - 1.0f), (1.0f - (2.0f * (mouseY)) / SCR_HEIGHT), depth * 2.0f - 1.0f, 1.0f);
    glm::mat4 projectionMatrix = gameInst[0].camera.GetProjectionMatrix((float)SCR_WIDTH / (float)SCR_HEIGHT);
    glm::vec4 viewCoords = glm::inverse(projectionMatrix) * clipCoords;
    viewCoords /= viewCoords.w;

    glm::vec4 worldCoords = glm::inverse(gameInst[0].camera.GetViewMatrix()) * viewCoords;
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
    if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
        return;
    }

    gameInst[0].handleLeftClick(getWorldPosition());
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
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Tractor Game", NULL, NULL);
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



