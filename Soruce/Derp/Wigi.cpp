#include <iostream>

#include "Wigi.h"

void penis();

Wigi::Wigi() : GameObject("Wigi") {
	
	SpriteRenderer* sprite_renderer = new SpriteRenderer();
	sprite_renderer->set_sprite("..\\Assets\\Wigi.png");
	this->add_component(sprite_renderer);

	InputHandler* input_handler = new InputHandler();
	input_handler->add_binding(sf::Keyboard::A, penis);
	this->add_component(input_handler);
}

void penis() {
	std::cout << "penis" << std::endl;
}

void Wigi::rotate_left() {
	std::cout << "rotate left" << std::endl;
}

void Wigi::rotate_right() {
	std::cout << "rotate right" << std::endl;
}

void Wigi::thrust() {
	std::cout << "Thrust" << std::endl;
}