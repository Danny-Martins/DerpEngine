#pragma once
#include <map>
#include <list>
#include <SFML\Graphics.hpp>
#include "Rigidbody.h"
#include "Component.h"
#include "GameObject.h"

class PhysicsEngine {
	public:
		float groundedTol = 0.1f;

		struct CollisionPair
		{
			Rigidbody *object_rigidbody_a;
			Rigidbody *object_rigidbody_b;
		};

		struct CollisionInfo
		{
			sf::Vector2f collisonNormal;
			float penatration;
		};

		static PhysicsEngine* phyisics_engine_instance;

	public:
		void add_rigidBody(Rigidbody* object_rigidbody);
		void update_gameobjects_phyisics(float delta_time);
		bool is_grounded(Rigidbody* object_rigidbody);
		PhysicsEngine();
		void update_phyisics(float delta_time);
		CollisionPair *pair = new CollisionPair();
		CollisionInfo *info = new CollisionInfo();

	private:
		std::map<CollisionPair*, CollisionInfo*> collision_list;
		std::list<Rigidbody*> rigidbodies_list;

	private:
		void check_collisions();
		void resolve_collisons();
		void correct_positions(CollisionPair *pair);
};