#include "GameObjectManager.h"
#include <iostream>

GameObjectManager* GameObjectManager::instance;

GameObjectManager::GameObjectManager() {
	GameObjectManager::instance = this;
}

void GameObjectManager::add_to_graph(GameObject* gameobject) {
	this->scene_graph.push_back(gameobject);
	std::cout << "Added " << gameobject->name << " to scene root" << std::endl;
	std::cout << scene_graph.size() << std::endl;
}

void GameObjectManager::start() {
	for (std::vector<GameObject*>::iterator itorator = this->scene_graph.begin(); itorator != this->scene_graph.end(); itorator++) {
		(*itorator)->start();
	}
}

void GameObjectManager::update(float delta_time) {
	for (std::vector<GameObject*>::iterator itorator = this->scene_graph.begin(); itorator != this->scene_graph.end(); itorator++) {
		(*itorator)->update(delta_time);
	}
}
