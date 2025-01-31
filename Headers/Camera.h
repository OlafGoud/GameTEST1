#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = 0.0f;
const float PITCH = 80.0f;
const float SPEED = 10.0f   ;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    glm::vec3 Target = glm::vec3(0, 0, 0);
    float OrbitRadius = 12;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void prosessWorldMovement(float xoffset, float yoffset) {
        // Scale offsets by sensitivity to control movement speed
        xoffset *= MouseSensitivity * 0.15f;
        yoffset *= MouseSensitivity * 0.15f;

        // Create movement direction vectors
        glm::vec3 forward = glm::normalize(glm::vec3(Front.x, 0.0f, Front.z)); // Forward direction (XZ plane)
        glm::vec3 right = glm::normalize(glm::cross(forward, WorldUp));        // Right direction

        // Update the position: xoffset affects the right vector, yoffset affects the forward vector
        Position += right * -xoffset; // Negative to align with drag direction
        Position += forward * -yoffset;
    }

    void moveCamWithObject(glm::vec3 movement) {
        Target += movement;
        updateCameraVectors();
    }


    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void processCameraMovement(float yawOffset, float pitchOffset, GLboolean constrainPitch = true)
    {

        Yaw += yawOffset * MouseSensitivity;
        Pitch += -pitchOffset * MouseSensitivity;

        // Clamp pitch to prevent flipping
        if (Pitch > 89.0f) Pitch = 89.0f;
        if (Pitch < 60.0f) Pitch = 60.0f;

        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 60.0f)
            Zoom = 60.0f;
    }

    glm::mat4 GetProjectionMatrix(float aspectRatio)
    {
        // glm::perspective(fov, aspect ratio, near, far)
        return glm::perspective(glm::radians(Zoom), aspectRatio, 0.1f, 100.0f);
    }


private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors() {
        // Calculate new camera position using orbit equations
        Position.x = Target.x + OrbitRadius * cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Position.y = Target.y + OrbitRadius * sin(glm::radians(Pitch));
        Position.z = Target.z + OrbitRadius * sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

        // Look at the target
        Front = glm::normalize(Target - Position);
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};
#endif