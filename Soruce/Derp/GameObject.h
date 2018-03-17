#pragma once

#include <string>
#include <vector>
#include "Component.h"
#include "Transform.h"

class GameObject {
	public:
		//static GameObject& find(std::string object_name);

		GameObject(std::string name, GameObject* parent);

		void add_child(GameObject* child);
		void set_parent(GameObject* parent);

		void add_component(Component* component);

		virtual void start();
		virtual void update(float deleta_time);
		void render();

		sf::Transform get_world_transform();


	public:
		std::string name;

		GameObject* parent;
		std::vector<GameObject*> children;
		std::vector<Component*> components;

		Transform* transform;
};