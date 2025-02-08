#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

class MovementController {
public:
	MovementController() {}
	~MovementController() {}

	void addInput(bool forward, bool backward, bool turnLeft, bool turnRight, float deltaTime);
	glm::vec3 getNewPosition(glm::vec3 currentPosition, float deltaTime);

	//variables
	//steering
	float currentSteeringRotation = 0.0f;
	float steeringSpeed = 0.0f;
	float maxSteeringRotation = 30.0f;
	float steeringCenteringSpeed = 10.0f;
	//movement
	float maxSpeed = 10.0f; // m/s
	float currentSpeed = 0.0f; // m/s
	float acceleration = 100.0f; // m/s^2
	float brakingSpeed = 4.0f; // m/s^2
	float engineBrakingSpeed = 0.4f; // m/s^2
	float maxBackwardsSpeed = 5.0f;
};

class CarController : public MovementController
{
public:
	CarController() {};
	~CarController() {};

};

