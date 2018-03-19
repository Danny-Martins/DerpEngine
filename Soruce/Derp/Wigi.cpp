#include <iostream>

#include "Wigi.h"
#include "Rigidbody.h"
#include "SpriteRenderer.h"
#include "MusicComponent.hpp"

#include "Debug.hpp"

Wigi::Wigi() : GameObject("Wigi", nullptr),  move_speed(1) {

	SpriteRenderer* sprite_renderer = new SpriteRenderer();
	sprite_renderer->set_sprite("..\\Assets\\Wigi.png");
	this->add_component(sprite_renderer);

	//this->transform->setScale(sf::Vector2f(0.25f, 0.25f));
	this->transform->setPosition(375.0f, 50.0f);

	/*
	InputHandler* input_handler = new InputHandler();
	//input_handler->add_binding(sf::Keyboard::A, penis);
	this->add_component(input_handler);
	*/
}

void Wigi::update(float delta_time) {
	GameObject::update(delta_time);

	sf::Vector2f temp_position = this->transform->getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		temp_position.x -= move_speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		temp_position.x += move_speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		temp_position.y -= move_speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		temp_position.y += move_speed;
	}
	
	this->transform->setPosition(temp_position);
	//this->transform->sf_transform.translate(temp_position).rotate(0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		this->transform->rotate(-0.25f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		this->transform->rotate(0.25f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		this->transform->scale(sf::Vector2f(0.995f, 0.995f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
		this->transform->scale(sf::Vector2f(1.005f, 1.005f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		Debug::log_error("YA DUN FUCKED UP", true);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
		Debug::clear_log();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		Debug::print("Words Words Words");
	}

	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		for (std::vector<Component*>::iterator itorator = this->components.begin(); itorator != this->components.end(); itorator++) {
			if (dynamic_cast<Rigidbody*> ((*itorator)) != NULL) {
				std::cout << "it worked!" << std::endl;
			}
		}
	}
	*/
}