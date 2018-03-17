#include "GameObject.h"
#include "GameObjectManager.h"
#include "SpriteRenderer.h"
#include <iostream>

GameObject::GameObject(std::string name, GameObject* parent){
	this->name = name;
	this->transform = new Transform();
	this->add_component(this->transform);

	if (parent == nullptr)
		GameObjectManager::instance->add_to_graph(this);
	else {
		parent->add_child(this);
		this->set_parent(parent);
	}
		
	//std::cout << "gameobject constructor" << std::endl;
	//if parent is null add to game object manager
}

void GameObject::add_component(Component* component) {
	component->game_object = this;
	component->start();
	this->components.push_back(component);
}

void GameObject::add_child(GameObject* child) {
	std::cout << "Added " << child->name << " as a child of " << this->name;
	this->children.push_back(child);
}

void GameObject::set_parent(GameObject* parent) {
	this->parent = parent;
}

void GameObject::start() {
	for (std::vector<Component*>::iterator itorator = this->components.begin(); itorator != this->components.end(); itorator++) {
		(*itorator)->start();
	}
}

void GameObject::update(float delta_time) {
	//sf::Transform transform = this->transform->getTransform();
	//transform.combine(this->parent->transform->getTransform());
	//this->transform->getTransform() = transform;

	for (std::vector<Component*>::iterator itorator = this->components.begin(); itorator != this->components.end(); itorator++) {
		(*itorator)->update(delta_time);
	}
	
	for (std::vector<GameObject*>::iterator itorator = this->children.begin(); itorator != this->children.end(); itorator++) {
		//sf::Transform transform = (*itorator)->transform->getTransform() * this->transform->getTransform();
		(*itorator)->update(delta_time);
	}

	if (this->name == "Uganda") {
		//this->transform->sf_transform.translate(sf::Vector2f(0.05f, 0.05f));
		//for(int row = 0; )
		
		//std::cout << *transform.getMatrix() << std::endl;
	}

	//std::cout << "gameobject" << std::endl;
}

sf::Transform GameObject::get_world_transform() {
	if (this->parent == nullptr)
		return this->transform->getTransform();

	return this->transform->getTransform() * this->parent->transform->getTransform();
	
}

