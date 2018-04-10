#include "Button.hpp"
#include "DerpEngine.h"

Button::Button() : button_box(), is_mouse_hovered(false){
	this->button_box.setFillColor(sf::Color::Black);
	this->button_box.setOutlineColor(sf::Color::White);
	this->button_box.setOutlineThickness(5);
	this->button_box.setSize(sf::Vector2f(450.0f, 200.0f));
}

void Button::start() {
	sf::Vector2f calculated_origin;
	calculated_origin.x = this->button_box.getLocalBounds().left + (this->button_box.getLocalBounds().width / 2);
	calculated_origin.y = this->button_box.getLocalBounds().top + (this->button_box.getLocalBounds().height / 2);
	this->button_box.setOrigin(calculated_origin);
}

//add functionality to check if the mouse position is within the bounds of the button
void Button::update(float delta_time) {
	//sf::Vector2i mouse_position = sf::Mouse::getPosition();
	DerpEngine::render_window->draw(this->button_box, this->game_object->get_world_transform());
}