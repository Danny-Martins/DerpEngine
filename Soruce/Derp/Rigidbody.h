#pragma once
#include <SFML\Graphics.hpp>
#include "Component.h"
#include "BoxCollider.hpp"

class PhysicsEngine;

class Rigidbody : public Component {
public:
	float mass = 1.0f;
	float bounciness;

	//The force that will slow down objects velocity (1.0f is no force)
	float linear_dampaning = 0.005f;
	//The threshold that will force the player to stop
	//moving if they pass this value
	float stopping_speed = 0.00004f;

	bool obeys_gravity = true;
	bool grounded;

	//const sf::Vector2f gravity = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f gravity = sf::Vector2f(0.0f, 0.00016f);
	const sf::Vector2f max_velocity = sf::Vector2f(0.25f, 0.25f);
	sf::Vector2f current_velocity;

	struct AABB
	{
		sf::Vector2f bottom_left;
		sf::Vector2f top_right;
	};

	AABB aabb;

public:
	Rigidbody();
	void add_force(sf::Vector2f force);
	void stop(bool stop_x_axis, bool stop_y_axis);
	bool is_grounded();
	void update(float delta_time) override;
	void start() override;
	void update_phyisics(float delta_time);
	void set_aabb();

private:
	sf::Vector2f total_forces;
	PhysicsEngine *engine;
	BoxCollider *box_collider;

private:
};