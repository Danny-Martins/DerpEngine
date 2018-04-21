#include "Transform.h"
#include <iostream>
#include <math.h>

#define PI 3.14159265

Transform::Transform() {}

void Transform::start(){}

void Transform::update(float delta_time){}

sf::Vector2f Transform::get_up_vector() {
	//sf::Vector2f(0.0f, 0.0f)
	return sf::Vector2f( sin(this->getRotation() * (PI / 180)) ,
							-cos(this->getRotation() * (PI / 180)));
}