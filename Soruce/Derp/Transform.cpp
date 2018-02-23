#include "Transform.h"
#include <iostream>

Transform::Transform() : position(), rotation(), scale(1, 1, 1){
	//
}

void Transform::start(){
	//
}

void Transform::update(){
	//
}

void Transform::translate(Vector3 translate_vector) {
	this->sf_transform.translate(sf::Vector2f(translate_vector.x, translate_vector.y));
	this->position.x += translate_vector.x;
	this->position.y += translate_vector.y;
	this->position.z += translate_vector.z;
}

void Transform::rotate(float degrees) {
	this->sf_transform.rotate(degrees);
	this->rotation.z += degrees;
}