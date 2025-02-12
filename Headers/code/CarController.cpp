#include "../CarController.h"

glm::vec3 MovementController::update(bool forward, bool backward, bool turnLeft, bool turnRight, float deltaTime, float& vehicleRotation)
{
	if (forward) {
		speed += acceleration * deltaTime;
		if (speed > maxSpeed)
			speed = maxSpeed;
	}
	// Gradual Deceleration
	// Gradual Deceleration when no input
	// Acceleration Backward
	else if (backward) {
		speed -= acceleration * deltaTime;
		if (speed < -maxSpeed / 2) // Limit reverse speed
			speed = -maxSpeed / 2;
	}
	else {
		if (speed > 0) {
			speed -= deceleration * deltaTime;
			if (speed < 0)
				speed = 0;
		}
		else if (speed < 0) {
			speed += deceleration * deltaTime;
			if (speed > 0)
				speed = 0;
		}
	}

	// Steering
	float rotation = 0.0f;
	if (turnLeft) {
		rotation = turnSpeed * deltaTime;
	}
	if (turnRight) {
		rotation = -turnSpeed * deltaTime;
	}
	vehicleRotation += rotation;

	// Apply steering using trigonometry
	float radians = glm::radians(vehicleRotation);
	direction.x = sin(radians);
	direction.z = cos(radians);
	direction = glm::normalize(direction);
	glm::vec3 returnValue = direction * speed * deltaTime;
	return returnValue;
}
