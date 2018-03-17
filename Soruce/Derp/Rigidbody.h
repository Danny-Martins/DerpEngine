#pragma once
#include <SFML\Graphics.hpp>
#include "Component.h"

class PhyisicsEngine;

class Rigidbody {
	public:
		float mass;
		float bounciness;

		bool obeys_gravity;
		bool grounded;

		sf::Vector2f gravity = sf::Vector2f(0.0f, -9.8f);
		sf::Vector2f max_velocity = sf::Vector2f(10.0f, 10.0f);
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
		void stop();
		bool is_grounded();
		void update(float delta_time);
		void start();
		void update_phyisics(float delta_time);

	private:
		sf::Vector2f total_forces;
		PhyisicsEngine *engine;

	private:
		void set_aabb();
};