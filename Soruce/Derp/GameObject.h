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

		template <typename component> component* get_component();

		virtual void start();
		virtual void update(const float deleta_time);
		void render();

		sf::Transform get_world_transform();


	public:
		std::string name;

		GameObject* parent;
		std::vector<GameObject*> children;
		std::vector<Component*> components;

		Transform* transform;

		sf::Vector2f bottom_left;
		sf::Vector2f top_right;

		float half_width;
		float half_height;
};