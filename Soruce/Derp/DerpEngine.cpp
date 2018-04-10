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

#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "DerpEngine.h"

#include "GameObject.h"

//game play gameobjects
#include "Wigi.h"
#include "Rigidbody.h"
#include "MusicComponent.hpp"
#include "SpriteRenderer.h"
#include "Debug.hpp"

sf::RenderWindow* DerpEngine::render_window;

DerpEngine::DerpEngine() : is_debug_mode(true), scene_root(), physics_engine(){

	std::cout << "starting app \n";

	engine_current_state = Uninitialized;

	std::thread hardware_check_thread(&DerpEngine::check_hardware, this);

	this->render_window = new sf::RenderWindow();
	this->init_graphics();
	this->display_splash_screen();

	hardware_check_thread.join();
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
	this->render_window->create({ 1280, 720 }, "Derp Engine");
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

	Debug::clear_log();
	
	GameObject* background = new GameObject("Background", nullptr);
	SpriteRenderer* background_sprite = new SpriteRenderer();
	background_sprite->set_sprite("..\\Assets\\Sprites\\test background.jpg");
	background->add_component(background_sprite);
	background->transform->setPosition(sf::Vector2f(1280/2, 720/2));
	MusicComponent* background_music = new MusicComponent();
	background_music->load_music("..\\Assets\\Audio\\BGM\\Daybreak.wav");
	background_music->play(false);
	
	GameObject* floor = new GameObject("Floor", nullptr);
	floor->add_component(new BoxCollider(1280 / 2, 40));
	floor->transform->setPosition(1280 / 2, 750.0f);
	Rigidbody* floor_rigidbody = new Rigidbody();
	floor_rigidbody->mass = 0.0f;
	floor_rigidbody->bounciness = 0.5f;
	floor->add_component(floor_rigidbody);

	GameObject* box = new GameObject("Ground", nullptr);
	SpriteRenderer* box_sprite = new SpriteRenderer();
	box_sprite->set_sprite("..\\Assets\\Sprites\\Box.png");
	box->add_component(box_sprite);
	box->transform->setScale(0.5f, 0.5f);

	BoxCollider* box_collider = new BoxCollider(64.0f, 64.0f);
	box->add_component(box_collider);
	
	Rigidbody* box_rigid = new Rigidbody();
	box_rigid->mass = 0.5f;
	box_rigid->bounciness = 0.5f;
	box->add_component(box_rigid);

	box->transform->setPosition(sf::Vector2f(250.0f, 570.0f));

	Wigi* wigi = new Wigi();
	
	GameObject* uganda = new GameObject("Uganda", wigi);
	SpriteRenderer* sprite_renderer = new SpriteRenderer();
	sprite_renderer->set_sprite("..\\Assets\\Sprites\\Uganda.png");
	uganda->add_component(sprite_renderer);
	

	GameObject* box2 = new GameObject("Ground", nullptr);
	SpriteRenderer* box_sprite2 = new SpriteRenderer();
	box_sprite2->set_sprite("..\\Assets\\Sprites\\Box.png");
	box2->add_component(box_sprite2);
	box2->transform->setScale(0.5f, 0.5f);

	BoxCollider* box_collider2 = new BoxCollider(64.0f, 64.0f);
	box2->add_component(box_collider2);

	Rigidbody* box_rigid2 = new Rigidbody();
	box_rigid2->mass = 0.5f;
	box_rigid2->bounciness = 0.5f;
	box2->add_component(box_rigid2);

	box2->transform->setPosition(sf::Vector2f(950.0f, 570.0f));

	GameObject* box3 = new GameObject("Ground", nullptr);
	SpriteRenderer* box_sprite3 = new SpriteRenderer();
	box_sprite3->set_sprite("..\\Assets\\Sprites\\Box.png");
	box3->add_component(box_sprite3);
	box3->transform->setScale(0.5f, 0.5f);

	BoxCollider* box_collider3 = new BoxCollider(64.0f, 64.0f);
	box3->add_component(box_collider3);

	Rigidbody* box_rigid3 = new Rigidbody();
	box_rigid3->mass = 0.5f;
	box_rigid3->bounciness = 0.5f;
	box3->add_component(box_rigid3);

	box3->transform->setPosition(sf::Vector2f(900.0f, 275.0f));

	//uganda->transform->setPosition(wigi->transform->getPosition().x, 0.0f);
	//Rigidbody* rigidbody = new Rigidbody();
	//uganda->add_component(rigidbody);
	//uganda->transform->setPosition(375.0f, 400.0f);

	//std::cout << std::endl << uganda->parent->name << std::endl;
}

void DerpEngine::main_loop() {

	this->setup_scene();
	//this->scene_root.start();

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

void DerpEngine::shutdown() {
	delete GameObjectManager::instance;
}