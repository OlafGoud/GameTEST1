#include "../CarController.h"

void MovementController::addInput(bool forward, bool backward, bool turnLeft, bool turnRight, float deltaTime)
{
	if (turnLeft) {
		//left
		MovementController::currentSteeringRotation -= MovementController::steeringSpeed * deltaTime;
		if (MovementController::currentSteeringRotation < -MovementController::maxSteeringRotation) {
			MovementController::currentSteeringRotation = -MovementController::maxSteeringRotation;
		}
	} 
	if (turnRight) {
		MovementController::currentSteeringRotation += MovementController::steeringSpeed * deltaTime;
		if (MovementController::currentSteeringRotation > MovementController::maxSteeringRotation) {
			MovementController::currentSteeringRotation = MovementController::maxSteeringRotation;
		}
	}
	if (forward) {
		MovementController::currentSpeed += MovementController::acceleration * deltaTime;
		if (MovementController::maxSpeed > MovementController::currentSpeed) {
			MovementController::currentSpeed = MovementController::maxSpeed;
		}
	}
	if (backward) {
		if (currentSpeed > 0.4f) {
			MovementController::currentSpeed -= MovementController::brakingSpeed * deltaTime;
			if (MovementController::currentSpeed < MovementController::maxBackwardsSpeed) {
				MovementController::currentSpeed = -MovementController::maxBackwardsSpeed;
			}
		}
		MovementController::currentSpeed -= MovementController::acceleration * deltaTime;
		if (MovementController::currentSpeed < MovementController::maxBackwardsSpeed) {
			MovementController::currentSpeed = -MovementController::maxBackwardsSpeed;
		}
	}
}

glm::vec3 MovementController::getNewPosition(glm::vec3 currentPosition, float deltaTime)
{
	float steeringAngleRad = glm::radians(currentSteeringRotation);

	// Forward direction (assuming +X is forward)
	glm::vec3 forwardDirection = glm::vec3(glm::cos(steeringAngleRad), 0.0f, glm::sin(steeringAngleRad));

	// Calculate displacement
	glm::vec3 displacement = forwardDirection * currentSpeed * deltaTime;

	// Update position
	currentPosition += displacement;

	// Reduce steering towards zero
	if (currentSteeringRotation > 0.3f) {
		currentSteeringRotation = glm::max(0.0f, currentSteeringRotation - steeringCenteringSpeed * deltaTime);
	}
	else if (currentSteeringRotation < -0.3f) {
		currentSteeringRotation = glm::min(0.0f, currentSteeringRotation + steeringCenteringSpeed * deltaTime);
	}
	else {
		currentSteeringRotation = 0;
	}

	// Apply engine braking
	if (currentSpeed > 0.3f) {
		currentSpeed -= brakingSpeed * deltaTime;
	}
	else if (currentSpeed < -0.3f) {
		currentSpeed += brakingSpeed * deltaTime;
	}
	else {
		currentSpeed = 0;
	}
	return currentPosition;
}
