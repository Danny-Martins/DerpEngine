#include "Rigidbody.h"
#include "PhyisicsEngine.h"
#include "iostream"
#include "SpriteRenderer.h"

Rigidbody::Rigidbody() {}

void Rigidbody::start(){
	Rigidbody::set_aabb();
	engine = PhysicsEngine::phyisics_engine_instance;
	engine->add_rigidBody(this);

	//this->game_object->get_component<SpriteRenderer>();
}

bool Rigidbody::is_grounded() {
	grounded = engine->is_grounded(this);
	return(grounded);
}

void Rigidbody::set_aabb(){
	//TODO get size of box from sprite
	aabb.bottom_left = this->game_object->bottom_left;
	aabb.top_right = this->game_object->top_right;
}

void Rigidbody::stop() {
	current_velocity = sf::Vector2f(0.0f, 0.0f);
	total_forces = sf::Vector2f(0.0f, 0.0f);
}

void Rigidbody::add_force(sf::Vector2f force) {
	total_forces += force;
}

void Rigidbody::update(float delta_time) {
}

void Rigidbody::update_phyisics(float delta_time) {
	if (obeys_gravity && !grounded)
		add_force(gravity);
	else
	{
		if (abs(current_velocity.y) < 0.05f)
			current_velocity.y = 0;
	}

	sf::Vector2f accleration = total_forces / mass;

	if (mass == 0)
		sf::Vector2f accleration = sf::Vector2f(0.0f, 0.0f);
	else
		sf::Vector2f accleration = total_forces / mass;

	current_velocity += accleration * delta_time;

	current_velocity.x = std::min(current_velocity.x, max_velocity.x);
	current_velocity.y = std::min(current_velocity.y, max_velocity.y);

	//std::cout << "X: " << current_velocity.x << "Y: " << current_velocity.y << std::endl;

	sf::Vector2f temp = this->game_object->transform->getPosition();
	temp += current_velocity * delta_time;

	this->game_object->transform->setPosition(temp);

	//std::cout << this->game_object->transform->getPosition().x << std::endl;
	set_aabb();

	total_forces = sf::Vector2f(0.0f, 0.0f);
}