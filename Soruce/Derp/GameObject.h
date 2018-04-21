#pragma once

#include "Component.h"
#include "Transform.h"

#include <string>

class GameObject {
	public:
		//static GameObject& find(std::string object_name);

		GameObject(std::string name, GameObject* parent);
		~GameObject();

		void add_child(GameObject* child);
		void set_parent(GameObject* parent);

		void add_component(Component* component);

		void start();
		void update(const float deleta_time);

		void boradcast_message(std::string message);

		sf::Transform get_world_transform();

		template <typename component>
		inline component* get_component() {
			for (std::vector<Component*>::iterator itorator = this->components.begin(); itorator != this->components.end(); itorator++) {
				if (dynamic_cast<component*> ((*itorator)) != NULL)
					return (component*)(*itorator);
			}
			return nullptr;
		}

	public:
		std::string name;

		GameObject* parent;
		std::vector<GameObject*> children;
		std::vector<Component*> components;

		Transform* transform;

		bool enabled;
};