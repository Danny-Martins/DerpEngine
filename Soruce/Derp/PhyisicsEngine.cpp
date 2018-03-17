#include "PhyisicsEngine.h"
#include <cmath>

PhyisicsEngine* PhyisicsEngine::phyisics_engine_instance;

PhyisicsEngine::PhyisicsEngine(){
	PhyisicsEngine::phyisics_engine_instance = this;
}

void PhyisicsEngine::add_rigidBody(Rigidbody* object_rigidbody){
	rigidbodies_list.push_back(object_rigidbody);
}

void PhyisicsEngine::update_gameobjects_phyisics(float delta_time)
{
	for each (Rigidbody *rigidbody in rigidbodies_list)
	{
		rigidbody->update_phyisics(delta_time);
	}
}

bool PhyisicsEngine::is_grounded(Rigidbody* object_rigidbody)
{
	for each (Rigidbody *rigidbody in rigidbodies_list)
	{
		if (rigidbody != object_rigidbody)
		{
			if (object_rigidbody->aabb.bottom_left.x < rigidbody->aabb.top_right.x
				&& object_rigidbody->aabb.top_right.x > rigidbody->aabb.bottom_left.x
				&& abs(object_rigidbody->aabb.bottom_left.y - rigidbody->aabb.top_right.y) <= groundedTol)
			{
				if (abs(object_rigidbody->current_velocity.y) < groundedTol)
					return true;
			}
		}
	}
	return false;
}

void PhyisicsEngine::check_collisions()
{
	for each (Rigidbody *rigidbody_a in rigidbodies_list) {
		for each (Rigidbody *rigidbody_b in rigidbodies_list) {
			CollisionPair pair;
			CollisionInfo info;

			pair.object_rigidbody_a = rigidbody_a;
			pair.object_rigidbody_b = rigidbody_b;

			sf::Vector2f distance;
			//

			sf::Vector2f halfSizeA = (rigidbody_a->aabb.top_right - rigidbody_a->aabb.bottom_left) * 0.5f;
			sf::Vector2f halfSizeB = (rigidbody_b->aabb.top_right - rigidbody_b->aabb.bottom_left) * 0.5f;

			sf::Vector2f gap = sf::Vector2f(abs(distance.x), abs(distance.y)) - (halfSizeA + halfSizeB);

			std::map<CollisionPair, CollisionInfo>::iterator it;
			it = collisionPair.find(pair);

			/*if (gap.x < 0 && gap.y < 0) {

				//if (it != collisionPair.end()) {
					//collisionPair.erase(pair);
				//}

				if (gap.x > gap.y) {
					if (distance.x > 0) {
						// ... Update collision normal
						info.collisonNormal = sf::Vector2f(1, 0);
					}
					else {
						// ... Update collision normal
						info.collisonNormal = sf::Vector2f(-1, 0);
					}
					info.penatration = gap.x;
				}
				else {
					if (distance.y > 0) {
						// ... Update collision normal
						info.collisonNormal = sf::Vector2f(0, 1);
					}
					else {
						// ... Update collision normal
						info.collisonNormal = sf::Vector2f(0, -1);
					}
					info.penatration = gap.y;
				}
				collisionPair.insert(std::pair<CollisionPair, CollisionInfo>(pair, info));
			}
			//else if (it != collisionPair.end()) {
			//	collisionPair.erase(pair);
			//}*/
		}
	}
}

void PhyisicsEngine::update_phyisics(float delta_time)
{
	//update_gameobjects_phyisics(delta_time);
	//check_collisions();
	//resolve_collisons();
}