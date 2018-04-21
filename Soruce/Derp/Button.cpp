#include "Button.hpp"
#include "DerpEngine.h"
#include "Debug.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>

Button::Button() : button_box(){
	this->button_box.setFillColor(this->normal_color);
	this->button_box.setOutlineColor(sf::Color::White);
	this->button_box.setOutlineThickness(1);
	this->button_box.setSize(sf::Vector2f(100.0f, 100.0f));
}

void Button::start() {
	/*
	sf::Vector2f calculated_origin;
	calculated_origin.x = this->button_box.getLocalBounds().left + (this->button_box.getLocalBounds().width / 2);
	calculated_origin.y = this->button_box.getLocalBounds().top + (this->button_box.getLocalBounds().height / 2);
	this->button_box.setOrigin(calculated_origin);
	*/

	sf::Vector2f temp_size = sf::Vector2f(this->width, this->height);
	this->button_box.setSize(temp_size);
}

//add functionality to check if the mouse position is within the bounds of the button
void Button::update(float delta_time) {
	//std::cout << sf::Mouse::getPosition(*DerpEngine::render_window).x << std::endl;
	
	sf::Vector2i mouse_position = sf::Mouse::getPosition(*DerpEngine::render_window);
	if (mouse_position.x <= this->game_object->transform->getPosition().x + this->width &&
		mouse_position.x >= this->game_object->transform->getPosition().x &&
		mouse_position.y <= this->game_object->transform->getPosition().y + this->height &&
		mouse_position.y >= this->game_object->transform->getPosition().y) {

		this->button_box.setFillColor(this->highlight_color);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			//Debug::print(this->message);
			this->game_object->boradcast_message(this->message);
		}
	}
	else
		this->button_box.setFillColor(this->normal_color);
	
	DerpEngine::render_window->draw(this->button_box, this->game_object->get_world_transform());
}