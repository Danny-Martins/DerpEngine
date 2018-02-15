#pragma once
// #ifndef

#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class DerpEngine {

public:
	const bool is_debug_mode;
	unsigned int mhz;

public:
	DerpEngine();
	void main_loop();

private:
	sf::RenderWindow render_window;

private:
	//bool init_python();
	//check hardware
	bool check_hardware();
	unsigned int check_enough_disk_space();
	unsigned int get_cpu_speed();
	std::string get_cpu_architecture();
	void check_memory();
	void check_io_devices();

	//init 
	void init_graphics();
	void init_audio();

	//main loop
};