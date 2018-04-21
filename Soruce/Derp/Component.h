#pragma once

#include <string>

class GameObject;

class Component{
	public:
		GameObject* game_object = nullptr;
		virtual void start() {};
		virtual void update(float delta_time) {};
		virtual void recive_message(std::string messsage) {};

	public:
		bool enabled = true;
};
