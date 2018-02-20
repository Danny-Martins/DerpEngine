#pragma once

#include <string>
#include <vector>

class GameObject {
	public:
		static GameObject& find(std::string object_name);

		GameObject(std::string name);

		void add_child(GameObject* child);
		void set_parent(GameObject& parent);

		void Start();
		void Update(float deleta_time);


	public:
		std::string name;

		GameObject* parent;
		std::vector<GameObject*> children;


};