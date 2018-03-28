#include "Wigi.h"
#include "SpriteRenderer.h"
#include "SoundComponent.hpp"
#include "InputHandeler.hpp"
#include "BoxCollider.hpp"

#include "Debug.hpp"

Wigi::Wigi() : GameObject("Wigi", nullptr),  move_speed(0.0025f) {

	SpriteRenderer* sprite_renderer = new SpriteRenderer();
	sprite_renderer->set_sprite("..\\Assets\\Sprites\\Wigi.png");
	this->add_component(sprite_renderer);

	this->transform->setScale(sf::Vector2f(0.5f, 0.5f));
	this->transform->setPosition(375.0f, 150.0f);
	//this->transform->setRotation(180.0f);

	sf::Vector2f bounding_box;
	bounding_box.x = sprite_renderer->get_sprite().getGlobalBounds().width * 0.25f;
	bounding_box.y = sprite_renderer->get_sprite().getGlobalBounds().height * 0.25f;
	BoxCollider* box_collider = new BoxCollider(bounding_box.x, bounding_box.y);
	this->add_component(box_collider);

	this->rigid_body = new Rigidbody();
	this->rigid_body->bounciness = 0.5f;
	this->add_component(this->rigid_body);

	SoundComponent* sound_component = new SoundComponent();
	sound_component->load_sound("..\\Assets\\Audio\\BGM\\scream.ogg");
	this->add_component(sound_component);

	//this->components.erase(components.begin()+1);
	//delete this->get_component<SpriteRenderer>();
	

	/*
	InputHandler* input_handler = new InputHandler();
	input_handler->add_binding(sf::Keyboard::A, someclass::somefunc);
	this->add_component(input_handler);
	*/
}

void Wigi::thrust() {
	Debug::print("Thrust!");
}

void Wigi::update(float delta_time) {
	GameObject::update(delta_time);
	
	sf::Vector2f temp_position = sf::Vector2f(0.0f, 0.0f);

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
	
	this->rigid_body->add_force(temp_position);
	//this->transform->setPosition(temp_position);
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

	sf::Vector2f derp = (*this->children.begin())->transform->getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		this->get_component<SoundComponent>()->play();
		this->get_component<Rigidbody>()->add_force(sf::Vector2f(0.0f, -0.09f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		derp.x += this->move_speed * 100.0f;
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		derp.x -= this->move_speed  * 100.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		derp.y -= this->move_speed * 100.0f;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		derp.y += this->move_speed  * 100.0f;
	}

	(*this->children.begin())->transform->setPosition(derp);
}