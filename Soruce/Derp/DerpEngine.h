#pragma once

#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <thread>

#include "Scene.h"
#include "PhyisicsEngine.h"

class DerpEngine {

public:
	static sf::RenderWindow *render_window;

	const bool is_debug_mode;
	unsigned int mhz;

public:
	DerpEngine();
	void main_loop();
	void shutdown();

private:
	
	PhysicsEngine physics_engine;
	Scene current_scene;

	enum ENGINE_STATE
	{
		Uninitialized,
		Initialized,
		InitializedFailed,
		Playing,
		Paused,
	};

	ENGINE_STATE engine_current_state;

private:

	//bool init_python();
	//check hardware
	void check_hardware();
	unsigned int check_enough_disk_space();
	unsigned int get_cpu_speed();
	std::string get_cpu_architecture();
	void check_memory();
	void check_joypads();
	void display_splash_screen();

	//init 
	void init_graphics();
};