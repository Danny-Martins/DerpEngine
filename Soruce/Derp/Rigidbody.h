#pragma once
#include <SFML\Graphics.hpp>
#include "Component.h"

class PhysicsEngine;

class Rigidbody : public Component {
	public:
		float mass = 1.0f;
		float bounciness;

		bool obeys_gravity = true;
		bool grounded;

		//const sf::Vector2f gravity = sf::Vector2f(0.0f, 0.0f);
		const sf::Vector2f gravity = sf::Vector2f(0.0f, 0.00001f);
		const sf::Vector2f max_velocity = sf::Vector2f(0.05f, 0.05f);
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
		void update(float delta_time) override;
		void start() override;
		void update_phyisics(float delta_time);
		void set_aabb();

	private:
		sf::Vector2f total_forces;
		PhysicsEngine *engine;

	private:
};