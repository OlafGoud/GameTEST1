#include "../World.h"

Scene ::~Scene()
{
}

Scene::Scene(Camera cam) {
	objectShader = Shader("resources/shaders/basic.vs", "resources/shaders/basic.fs");
	terrainShader = Shader("resources/shaders/height.vs", "resources/shaders/height.fs");
	cam1 = cam;
	std::cout << "Loading models...\n";
	Scene::models = {
		{Model("resources/objects/pickaxe_stone.obj"), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f},
		{Model("resources/objects/pickaxe_stone.obj"), glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f}
	};
	Scene::cube.push_back({Model("resources/objects/cube.obj"), glm::vec3(0, 15, 0), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f});
	previewModels.push_back(Model("resources/objects/housetransparent.obj"));

	std::cout << "Loading world into memory...\n";
	terrain = Terrain("resources/maps/heightmap3.png");
	terrainHeightPerPoint = terrain.getHeightMap();
	std::cout << "World loaded into memory\n";
}


void Scene::addComponent(glm::vec3 pos) {
	Scene::models.push_back({ Model("resources/objects/house.obj"),  snapTo3DGrid(pos), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f });
}




void Scene::loadScene(glm::mat4 view, glm::mat4 projection) {
	terrainShader.use();
	terrainShader.setMat4("projection", projection);
	terrainShader.setMat4("view", view);
	loadWorld();
	objectShader.use();
	objectShader.setMat4("projection", projection);
	objectShader.setMat4("view", view);

	loadObjects();

}


void Scene::loadWorld() {

	terrain.renderTerrain(terrainShader, cam1);
}

void Scene::loadObjects() {

	for (auto obj : models) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, obj.position); // translate it down so it's at the center of the scene
		model = glm::scale(model, obj.scaling);	// it's a bit too big for our scene, so scale it down
		objectShader.setMat4("model", model);
		obj.model.Draw(objectShader);
	}


	

}

void Scene::loadCube(glm::mat4 view, glm::mat4 projection, float amount) {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, cube.at(0).position);
	model = glm::scale(model, cube.at(0).scaling);
	model = glm::rotate(model, glm::radians(amount), glm::vec3(0.0f, 1.0f, 0.0f));
	objectShader.setMat4("model", model);
	cube.at(0).model.Draw(objectShader);
}


glm::vec3 Scene::snapTo3DGrid(glm::vec3 position) {
	float gridSize = 1;
	position.x = round(position.x / gridSize) * gridSize;
	position.y = round(position.y / gridSize) * (gridSize / 10);
	position.z = round(position.z / gridSize) * gridSize;
	return position;
}



Shader* Scene::getTerrainShader() {
	return &terrainShader;
}


Shader* Scene::getObjectShader() {
	return &objectShader;
}


void Scene::loadPreview(int number, glm::vec3 pos) {
	if (number == 0) {
		return;
	}
	if (pos.x < 50 && pos.x > 20 && pos.z < 50 && pos.z > 20) {
		objectShader.use();
		// material properties
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, snapTo3DGrid(pos)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
		objectShader.setMat4("model", model);
		previewModels.at(number - 1).Draw(objectShader);
	}
}

