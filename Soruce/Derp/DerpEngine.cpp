#pragma once
// #ifndef

#include <string>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

#include <Windows.h>
#include <WinBase.h>
#include <direct.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "DerpEngine.h"

#include "GameObject.h"

//game play gameobjects
#include "Wigi.h"
#include "Rigidbody.h"
#include "SpriteRenderer.h"

sf::RenderWindow* DerpEngine::render_window;

DerpEngine::DerpEngine() : is_debug_mode(true), scene_root(), physics_engine(){

	std::cout << "starting app \n";

	engine_current_state = Uninitialized;

	std::thread hardware_check_thread(&DerpEngine::check_hardware, this);


	this->render_window = new sf::RenderWindow();
	this->init_graphics();
	this->display_splash_screen();

	hardware_check_thread.join();

	//this->main_loop();
}

void DerpEngine::check_hardware() {
	std::cout << "Starting init" << std::endl;

	this->check_enough_disk_space();
	this->get_cpu_speed();
	this->get_cpu_architecture();
	this->check_memory();
	this->check_joypads();

	engine_current_state = Initialized;

	std::cout << "hardware cheked son \n" << std::endl;

	return;
}


unsigned int DerpEngine::check_enough_disk_space() {
	const DWORDLONG disk_bytes_needed = 300000000;

	int const drive = _getdrive();
	//int const drive = 0;
	struct _diskfree_t diskfree;
	_getdiskfree(drive, &diskfree);
	unsigned __int64 const needed_clusters = disk_bytes_needed /
		(diskfree.sectors_per_cluster*diskfree.bytes_per_sector);
	if (diskfree.avail_clusters < needed_clusters) {
		std::cout << "ERROR NOT ENOUGH SPACE" << std::endl;
		assert(false);
	}
	return true;
}

unsigned int DerpEngine::get_cpu_speed() {

	DWORD buffer_size = sizeof(DWORD);
	DWORD mhz = 0;
	DWORD value_type = REG_DWORD;
	HKEY hive_key;

	long error_type = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hive_key);
	if (error_type == ERROR_SUCCESS) {
		RegQueryValueEx(hive_key,
			"~MHz", NULL, &value_type, (LPBYTE)&mhz, &buffer_size);
	}
	else {
		std::cout << "Could get CPU speed";
		return 0;
	}

	assert(mhz > 1000);

	return mhz;
}

std::string DerpEngine::get_cpu_architecture() {

	TCHAR architecture[1024];
	DWORD architecture_length = sizeof(architecture);
	DWORD value_type = REG_SZ;
	HKEY hive_key;
	long error_type = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		TEXT("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"), 0, KEY_READ, &hive_key);
	if (error_type == ERROR_SUCCESS) {
		RegQueryValueEx(hive_key, TEXT("ProcessorNameString"), NULL, &value_type,
			reinterpret_cast<LPBYTE>(&architecture), &architecture_length);
	}
	std::cout << architecture << std::endl;

	return "DERP";
}

void DerpEngine::check_memory() {

	MEMORYSTATUSEX memoryStatus = { sizeof memoryStatus };
	GlobalMemoryStatusEx(&memoryStatus);

	const DWORDLONG phyiscal_memory = memoryStatus.ullAvailPhys;

	DWORDLONG virtual_memory = memoryStatus.ullAvailVirtual;

	assert(phyiscal_memory > 90555520);
	assert(virtual_memory > 90555520);

	std::cout << "You have " << phyiscal_memory << " avaliable bytes for phyisical memory." << std::endl;

	std::cout << "You have " << virtual_memory << " avaliable bytes for virtual memory." << std::endl;

}

void DerpEngine::check_joypads() {
	int i = 0;
	while (sf::Joystick::isConnected(i)) {
		std::cout << "Joystick " << i << " is connected" << std::endl;
		i++;
	}
}

void DerpEngine::init_graphics() {
	this->render_window->create({ 800, 600 }, "Derp Engine");
}

void DerpEngine::display_splash_screen(){

	sf::Texture image;

	if (!image.loadFromFile("..\\Assets\\SplashScreen.jpg"))
	{
		std::cout << "Error could not load splash screen image" << std::endl;
		return;
	}

	sf::Sprite sprite(image);

	while (engine_current_state != Initialized)
	{
		render_window->clear();
		render_window->draw(sprite);
		this->render_window->display();
	}
}

void DerpEngine::setup_scene() {

	Wigi* wigi = new Wigi();
	/*
	GameObject* uganda = new GameObject("Uganda", nullptr);
	SpriteRenderer* sprite_renderer = new SpriteRenderer();
	sprite_renderer->set_sprite("..\\Assets\\Uganda.png");
	uganda->half_width = sprite_renderer->get_sprite().getGlobalBounds().width / 2;
	uganda->half_height = sprite_renderer->get_sprite().getGlobalBounds().height / 2;
	uganda->add_component(sprite_renderer);
	//Rigidbody* rigidbody = new Rigidbody();
	//uganda->add_component(rigidbody);
	uganda->transform->setPosition(375.0f, 400.0f);
	*/

	//std::cout << std::endl << uganda->parent->name << std::endl;
}

void DerpEngine::main_loop() {

	this->setup_scene();
	this->scene_root.start();

	sf::Clock delta_time_clock;

	while (this->render_window->isOpen())
	{
		
		sf::Event event;

		while (this->render_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->render_window->close();
		}

		float delta_time = (float)delta_time_clock.restart().asMilliseconds();
		this->render_window->clear();
		this->physics_engine.update_phyisics(delta_time);
		this->scene_root.update(delta_time);
		this->render_window->display();
	}
}