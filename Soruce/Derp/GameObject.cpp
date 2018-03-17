#include "GameObject.h"
#include "GameObjectManager.h"

GameObject::GameObject(std::string name) : parent(nullptr){
	this->name = name;
	this->transform = new Transform();
	this->add_component(this->transform);
	GameObjectManager::instance->add_to_graph(this);
	//if parent is null add to game object manager
}

void GameObject::add_component(Component* component) {
	this->components.push_back(component);
}

void GameObject::add_child(GameObject* child) {
	this->children.push_back(child);
}

void GameObject::set_parent(GameObject& parent) {
	this->parent = &parent;
}

void GameObject::start() {
	for (std::vector<Component*>::iterator itorator = this->components.begin(); itorator != this->components.end(); itorator++) {
		(*itorator)->start();
	}
}

void GameObject::update(float delta_time) {
	for (std::vector<Component*>::iterator itorator = this->components.begin(); itorator != this->components.end(); itorator++) {
		(*itorator)->update(delta_time);
	}
}



