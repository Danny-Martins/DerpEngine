#include "Rigidbody.h"
#include <cmath>
#include "PhyisicsEngine.h"

Rigidbody::Rigidbody(){
	
}

void Rigidbody::start(){
	Rigidbody::set_aabb();
	engine = PhyisicsEngine::phyisics_engine_instance;
	engine->add_rigidBody(this);
}

bool Rigidbody::is_grounded() {
	grounded = engine->is_grounded(this);
	return(grounded);
}

void Rigidbody::set_aabb(){

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

	sf::Vector2f temp;
	temp += current_velocity * delta_time;

	set_aabb();

	total_forces = sf::Vector2f(0.0f, 0.0f);
}