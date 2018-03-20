#pragma once

#include "GameObject.h"

class GameObjectManager {
	public:
		GameObjectManager();
		~GameObjectManager();

		static GameObjectManager* instance;
		
		void add_to_graph(GameObject* game_object);
		void start();
		void update(float delta_time);
		void shutdown();

	private:
		std::vector<GameObject*> scene_graph;
};

