#include "GameObject.h"

GameObject::GameObject(std::string name) : parent(nullptr) {
	this->name = name;
}

void GameObject::add_child(GameObject* child) {
	this->children.push_back(child);
}

void GameObject::set_parent(GameObject& parent) {
	this->parent = &parent;
}

void GameObject::Start() {
	
}

void GameObject::Update(float delta_time) {

}



