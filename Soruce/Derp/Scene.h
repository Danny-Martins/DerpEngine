#pragma once

#include "GameObject.h"

class Scene {
	public:
		Scene();
		~Scene();

		void build_scene_from_xml();

		static GameObject* scene_root;
		static GameObject* find(std::string name);

	private:
		void shutdown();
};

