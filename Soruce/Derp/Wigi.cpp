#include <iostream>

#include "Wigi.h"
#include "SpriteRenderer.h"

Wigi::Wigi() : GameObject("Wigi", nullptr),  move_speed(1) {

	SpriteRenderer* sprite_renderer = new SpriteRenderer();
	sprite_renderer->set_sprite("..\\Assets\\Wigi.png");
	this->add_component(sprite_renderer);

	BoxCollider* box_collider = new BoxCollider(sprite_renderer->get_sprite().getGlobalBounds().width * 0.5f,
		sprite_renderer->get_sprite().getGlobalBounds().height * 0.5f);
	this->add_component(box_collider);

	rigidbody = new Rigidbody();
	rigidbody->mass = 1.0f;
	rigidbody->bounciness = 0.5f;
	this->add_component(rigidbody);
	
	//this->transform->setScale(sf::Vector2f(0.25f, 0.25f));
	this->transform->setPosition(700.0f, 50.0f);

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		this->rigidbody->stop(false,true);
		this->rigidbody->add_force(jump_force);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->rigidbody->add_force(sf::Vector2f(0.02, 0));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->rigidbody->add_force(sf::Vector2f(-0.02, 0));
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