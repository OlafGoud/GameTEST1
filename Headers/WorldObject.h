#pragma once
#include <string>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Model.h"
#include "Camera.h"
#include "CarController.h"

class WorldObject {
public:
	WorldObject() {}
	~WorldObject() {}
	void render(Shader& shader);

	Model model;
	glm::vec3 position;
	float rotation;
	bool visableToRender;
	glm::vec3 scaling;
	std::string objectID;
};

class StaticWorldObject : public WorldObject
{
public:
	StaticWorldObject() {}
	~StaticWorldObject() {}
};

class Moveable : public WorldObject {
public:
	Moveable() {}
	~Moveable() {}
	void move(bool forward, bool backward, bool left, bool right, float deltaTime, Camera& camera);
	
	float maxSpeed;
};

//attachments
class VehicleAttachment : public WorldObject {
public:
	VehicleAttachment() {};
	~VehicleAttachment() {};
	void buttonInteract(int button, int modifier) {};
	void move() {};
};


class Vehicle : public Moveable {
public:
	Vehicle() {}
	~Vehicle() {}
	void addInput(bool forward, bool backward, bool turnLeft, bool turnRight, float deltaTime);
	void getNewPosition(float deltaTime);
	CarController controller = CarController();
};


class Tractor : public Vehicle {
public:
	Tractor(std::string modelPath, std::string objectID, glm::vec3 pos = glm::vec3(0.0f, 0.2f, 0.0f), float rotation = 0.0f, bool visable = true, glm::vec3 scale = glm::vec3(1.0f));
	~Tractor() {};
	VehicleAttachment attachment;
};

class Player : public Moveable {
public:
	Player(std::string modelPath, std::string objectID, glm::vec3 pos = glm::vec3(0.0f, 0.2f, 0.0f), float rotation = 0.0f, bool visable = true, glm::vec3 scale = glm::vec3(0.5f), float speed = 2.0f);
	~Player() {}
};




class EmptyAttachment : public VehicleAttachment {
public:
};

class TrailerAttachment : public VehicleAttachment {
public:
	void move();
	void buttonInteract(int button, int modifier);

};

class FixedAttachment : public VehicleAttachment {
public:
	void move();
	void buttonInteract(int button, int modifier);
};