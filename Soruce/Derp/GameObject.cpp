#include "GameObject.h"
#include "Scene.h"
#include "Debug.hpp"

GameObject::GameObject(std::string name, GameObject* parent) : enabled(true){
	this->name = name;
	this->transform = new Transform();
	this->add_component(this->transform);

	if (parent == nullptr){
		if (Scene::scene_root != nullptr) {
			Scene::scene_root->add_child(this);
		}
	}
	else {
		parent->add_child(this);
		this->set_parent(parent);
	}
}

GameObject::~GameObject() {
	if (this->children.size() != 0) {
		for (std::vector<GameObject*>::iterator itorator = this->children.begin(); itorator != this->children.end(); itorator++) {
			delete (*itorator);
		}
	}
	for (std::vector<Component*>::iterator itorator = this->components.begin(); itorator != this->components.end(); itorator++) {
		delete (*itorator);
	}
}

void GameObject::add_component(Component* component) {
	component->game_object = this;
	this->components.push_back(component);
}

void GameObject::add_child(GameObject* child) {
	//std::cout << "Added " << child->name << " as a child of " << this->name;
	this->children.push_back(child);
}

void GameObject::set_parent(GameObject* parent) {
	this->parent = parent;
}

void GameObject::start() {

	//Debug::print("start");
	if (!this->enabled)
		return;

	for (std::vector<Component*>::iterator itorator = this->components.begin(); itorator != this->components.end(); itorator++) {
		if((*itorator)->enabled)
			(*itorator)->start();
	}

	for (std::vector<GameObject*>::iterator itorator = this->children.begin(); itorator != this->children.end(); itorator++) {
		(*itorator)->start();
	}
}

void GameObject::update(const float delta_time) {

	if (!this->enabled)
		return;

	for (std::vector<Component*>::iterator itorator = this->components.begin(); itorator != this->components.end(); itorator++) {
		if ((*itorator)->enabled)
			(*itorator)->update(delta_time);
	}
	
	for (std::vector<GameObject*>::iterator itorator = this->children.begin(); itorator != this->children.end(); itorator++) {
		(*itorator)->update(delta_time);
	}
}

void GameObject::boradcast_message(std::string message) {
	for (std::vector<GameObject*>::iterator gameobject_itorator = Scene::scene_root->children.begin(); gameobject_itorator != Scene::scene_root->children.end(); gameobject_itorator++) {
		for (std::vector<Component*>::iterator itorator = (*gameobject_itorator)->components.begin(); itorator != (*gameobject_itorator)->components.end(); itorator++) {
			(*itorator)->recive_message(message);
		}
	}
}

sf::Transform GameObject::get_world_transform() {
	if (this->parent == nullptr)
		return this->transform->getTransform();

	return this->transform->getTransform() * this->parent->transform->getTransform();
}
