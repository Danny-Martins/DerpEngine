#pragma once

#include <string>
#include <vector>
#include "Component.h"
#include "Transform.h"

class GameObject {
	public:
		//static GameObject& find(std::string object_name);

		GameObject(std::string name);

		void add_child(GameObject* child);
		void set_parent(GameObject& parent);

		void add_component(Component* component);

		void start();
		void update(float deleta_time);


	public:
		std::string name;

		GameObject* parent;
		std::vector<GameObject*> children;
		std::vector<Component*> components;

		Transform* transform;
};