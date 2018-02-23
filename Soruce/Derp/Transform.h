#pragma once

#include "Component.h"
#include "SFML\Graphics.hpp"
#include "Vector.h"

class Transform : public Component, sf::Transformable{
public:
	Transform();
	void start();
	void update();

	void translate(Vector3 vector);
	void rotate(float degrees);
	
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

private:
	sf::Transform sf_transform;
};
