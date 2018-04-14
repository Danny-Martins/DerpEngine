#include "Lander.hpp"
#include "SpriteRenderer.h"
#include "BoxCollider.hpp"
#include "Rigidbody.h"
#include "SoundComponent.hpp"
#include "InputHandeler.hpp"

Lander::Lander() : GameObject("Player Lander", nullptr), thrust_power(1) {

	SpriteRenderer *sprite_renderer = new SpriteRenderer();
	sprite_renderer->set_sprite("..\\Assets\\Sprites\\Ship.png");
	this->add_component(sprite_renderer);

	sf::Vector2f bounding_box;
	bounding_box.x = sprite_renderer->get_sprite().getGlobalBounds().width * 0.25f;
	bounding_box.y = sprite_renderer->get_sprite().getGlobalBounds().height * 0.25f;
	BoxCollider* box_collider = new BoxCollider(bounding_box.x, bounding_box.y);
	this->add_component(box_collider);

	Rigidbody *rigid_body = new Rigidbody();
	rigid_body->bounciness = 0.5f;
	this->add_component(rigid_body);

	//InputHandler *input_handeler = new InputHandler();

	/*
	SoundComponent* sound_component = new SoundComponent();
	sound_component->load_sound("..\\Assets\\Audio\\BGM\\scream.ogg");
	this->add_component(sound_component);
	*/

	this->transform->setPosition(sf::Vector2f(650, 0));
	this->transform->setScale(0.5f, 0.5f);
}

void Lander::rotate(float scalar) {

}

void Lander::thrust() {

}

void Lander::start() {
	//GameObject::start();
	//this->transform->setPosition(sf::Vector2f(350, 0));
}

void Lander::update(float delta_time) {
	GameObject::update(delta_time);
}