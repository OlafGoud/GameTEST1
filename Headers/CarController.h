#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <iostream>

class MovementController {
public:
	MovementController() {}
	~MovementController() {}

	glm::vec3 update(bool forward, bool backward, bool turnLeft, bool turnRight, float deltaTime, float& vehicleRotation);

	//variables
	//steering
	float steeringAngle = 0.0f;
	float turnSpeed = 90.0f;
	float maxSpeed = 10.0f; // m/s
	float speed = 0.0f; // m/s
	float acceleration = 20.0f; // m/s^2
	float deceleration = 5.0f;
	float brakingForce = 10.0f; // m/s^2
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);

};

class CarController : public MovementController
{
public:
	CarController() {};
	~CarController() {};

};

