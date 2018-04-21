#pragma once

#include "Component.h"
#include "SFML\Graphics.hpp"

class Transform : public Component, public sf::Transformable{
public:
	Transform();
	void start() override;
	void update(float delta_time) override;
	sf::Vector2f get_up_vector();
};
