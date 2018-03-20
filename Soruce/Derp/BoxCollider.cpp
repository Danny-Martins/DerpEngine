#include "BoxCollider.hpp"
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "DerpEngine.h"

BoxCollider::BoxCollider(float half_width, float half_height) : draw_bounding_box(true){
	this->half_width = half_width;
	this->half_height = half_height;
}

void BoxCollider::start() {
	if (draw_bounding_box) {
		this->bounding_box = sf::RectangleShape(sf::Vector2f(this->half_width * 2.0f, this->half_height * 2.0f));
		sf::Vector2f calculated_origin = sf::Vector2f(0.0f, 0.0f);
		calculated_origin.x += this->half_width;
		calculated_origin.y += this->half_height;
		bounding_box.setOrigin(calculated_origin);
		bounding_box.setFillColor(sf::Color(0, 0, 0, 0));
		bounding_box.setOutlineColor(sf::Color(0, 255, 0));
		bounding_box.setOutlineThickness(1.0f);
	}
}

void BoxCollider::update(float delta_time) {

	this->bottom_left = this->game_object->transform->getPosition();
	this->bottom_left.x -= this->half_width;
	this->bottom_left.y -= this->half_height;

	this->top_right = this->game_object->transform->getPosition();
	this->top_right.x += this->half_width;
	this->top_right.y += this->half_height;

	if (draw_bounding_box) {
		bounding_box.setPosition(this->game_object->transform->getPosition());
		DerpEngine::render_window->draw(this->bounding_box);
	}
		
	
}