
#ifndef WORLDOBJECT
#define WORLDOBJECT

#pragma once
#include <string>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Model.h"
#include "Camera.h"
#include "CarController.h"
#include <glad/glad.h>
#include "Shader.h"

//#include "Game.h"

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
	virtual void buttonInteract(int button) { std::cout << "virtual"; };
	void move() {};

	bool working = false;
	std::string derivedClassID = "VehicleAttachment";

};


class Vehicle : public Moveable {
public:
	Vehicle(VehicleAttachment& att) {}
	Vehicle() = default;
	~Vehicle() {}
	void addInput(bool forward, bool backward, bool turnLeft, bool turnRight, float deltaTime, Camera& camera, Shader& shader, VehicleAttachment& attachment);
	CarController controller = CarController();
	std::string attachmentID;
};


class Tractor : public Vehicle {
public:
	Tractor(std::string modelPath, std::string objectID, glm::vec3 pos = glm::vec3(0.0f, 0.2f, 0.0f), float rotation = 0.0f, bool visable = true, glm::vec3 scale = glm::vec3(1.0f));
	~Tractor() {};
};

class Player : public Moveable {
public:
	Player(std::string modelPath, std::string objectID, glm::vec3 pos = glm::vec3(0.0f, 0.2f, 0.0f), float rotation = 0.0f, bool visable = true, glm::vec3 scale = glm::vec3(0.5f), float speed = 2.0f);
	~Player() {}
};




class EmptyAttachment : public VehicleAttachment {
public:
	EmptyAttachment() { derivedClassID = "EmptyAttachment"; }

};

class TrailerAttachment : public VehicleAttachment {
public:
	TrailerAttachment(std::string modelPath, std::string objectID, glm::vec3 pos = glm::vec3(0.0f, 0.2f, 0.0f), float rotation = 0.0f, bool visable = true, glm::vec3 scale = glm::vec3(0.5f));
	void move();
	void buttonInteract(int button);

};

class FixedAttachment : public VehicleAttachment {
public:
	FixedAttachment() {}
	FixedAttachment(std::string modelPath, std::string objectID, glm::vec3 pos = glm::vec3(0.0f, 0.2f, 0.0f), float rotation = 0.0f, bool visable = true, glm::vec3 scale = glm::vec3(0.5f));
	void move();
	void buttonInteract(int button) override;
};
#endif 