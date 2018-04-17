#include "PlayerComponent.hpp"

#include <SFML/Window/Keyboard.hpp>
#include "Scene.h"

PlayerComponent::PlayerComponent() : player_gui_fuel(nullptr){}

void PlayerComponent::start() {
	this->player_gui_fuel = Scene::find("Player GUI")->get_component<TextRenderer>();
	this->player_gui_fuel->set_string("Remaining Fuel: " + std::to_string((int)this->remaining_fuel));
}

void PlayerComponent::update(const float delta_time) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->rotate(-this->rotation_speed);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->rotate(this->rotation_speed);

}

void PlayerComponent::rotate(const float rotation_angle){
	this->game_object->transform->rotate(rotation_angle);
}