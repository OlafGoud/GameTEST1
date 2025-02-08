#include "../WorldObject.h"

void WorldObject::render(Shader& shader) {
	if (!visableToRender) {
		return;
	}
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, position);
	matrix = glm::rotate(matrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	matrix = glm::scale(matrix, scaling);
	shader.setMat4("model", matrix);
	model.Draw(shader);
}

void Moveable::move(bool forward, bool backward, bool left, bool right, float deltaTime, Camera& camera) {
	// Only update rotation if the car is moving
	if (left) {
		rotation += 90.0f * deltaTime; // Counterclockwise rotation
	}
	if (right) {
		rotation -= 90.0f * deltaTime; // Clockwise rotation
	}

	// Normalize the rotation angle to keep it between 0 and 360 degrees
	if (rotation > 360.0f) rotation -= 360.0f;
	if (rotation < 0.0f) rotation += 360.0f;

	// Calculate the forward direction based on the car's rotation (ignoring the Y-axis)
	glm::vec3 forwardDirection;
	forwardDirection.x = -cos(glm::radians(rotation - 90));  // X movement based on rotation
	forwardDirection.z = sin(glm::radians(rotation - 90));   // Z movement based on rotation
	forwardDirection.y = 0.0f;  // Ensure no vertical movement

	// Normalize to keep the speed consistent
	forwardDirection = glm::normalize(forwardDirection);

	// Update the position for forward/backward movement
	if (forward) {
		glm::vec3 movement = forwardDirection * maxSpeed * deltaTime;
		position += movement;
		camera.moveCamWithObject(movement);
	}
	if (backward) {
		glm::vec3 movement = -forwardDirection * maxSpeed * deltaTime;
		position += movement;
		camera.moveCamWithObject(movement);
	}
}



Tractor::Tractor(std::string modelPath, std::string objectID, glm::vec3 pos, float rotation, bool visable, glm::vec3 scale)
{
	Tractor::model = Model(modelPath);
	Tractor::objectID = objectID;
	Tractor::position = pos;
	Tractor::rotation = rotation;
	Tractor::visableToRender = visable;
	Tractor::scaling = scale;

}

Player::Player(std::string modelPath, std::string objectID, glm::vec3 pos, float rotation, bool visable, glm::vec3 scale, float speed)
{
	Player::model = Model(modelPath);
	Player::objectID = objectID;
	Player::position = pos;
	Player::rotation = rotation;
	Player::visableToRender = visable;
	Player::scaling = scale;
	Player::maxSpeed = speed;
}

void Vehicle::addInput(bool forward, bool backward, bool turnLeft, bool turnRight, float deltaTime)
{
	Vehicle::controller.addInput(forward, backward, turnLeft, turnRight, deltaTime);
}

void Vehicle::getNewPosition(float deltaTime)
{
	Vehicle::position = Vehicle::controller.getNewPosition(Vehicle::position, deltaTime);
}
