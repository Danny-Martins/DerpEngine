#include "PlayerComponent.hpp"

#include <SFML/Window/Keyboard.hpp>
#include "Scene.h"
#include "DerpEngine.h"
#include <cstdlib>

PlayerComponent::PlayerComponent() : player_gui_fuel(nullptr), crash_velocity_threshold(0.1f){

	this->player_name = std::getenv("USERNAME");
	Debug::print(this->player_name);

}

void PlayerComponent::start() {
	this->game_object->enabled = true;
	this->enabled = true;

	this->remaining_fuel = this->max_fuel;

	this->game_object->transform->setPosition(this->start_position);
	this->game_object->transform->setRotation(0);

	this->player_gui_fuel = Scene::find("Player GUI")->get_component<TextRenderer>();
	this->player_gui_fuel->set_string("Remaining Fuel: " + std::to_string((int)this->remaining_fuel));
	this->rigid_body = this->game_object->get_component<Rigidbody>();

	Scene::find("Player Name")->get_component<TextRenderer>()->set_string("Name: " + this->player_name);

	Scene::find("Game Over Menu")->enabled = false;
	Scene::find("Quit Button")->enabled = false;
	Scene::find("Restart Button")->enabled = false;
}

void PlayerComponent::update(const float delta_time) {

	//std::cout << this->game_object->transform->getRotation() << std::endl;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->rotate(-this->rotation_speed);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->rotate(this->rotation_speed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		this->thrust();

}

void PlayerComponent::rotate(const float rotation_angle){
	this->game_object->transform->rotate(rotation_angle);
}

void PlayerComponent::thrust() {
	if (this->remaining_fuel <= 0)
		return;
	
	this->remaining_fuel -= this->fuel_spend_amount;
	this->rigid_body->add_force(this->game_object->transform->get_up_vector() * this->thrust_power);
	this->player_gui_fuel->set_string("Remaining Fuel: " + std::to_string((int)this->remaining_fuel));
}

void PlayerComponent::recive_message(const std::string message){
	//all collision handled here
	if (message == "Wall") {
		this->game_object->enabled = false;
		this->show_end_screen(true);
	}
	else if (message == "Landing Zone") {
		if (this->rigid_body->current_velocity.x >= this->crash_velocity_threshold ||
			this->rigid_body->current_velocity.y >= this->crash_velocity_threshold) {

			this->game_object->enabled = false;
			this->show_end_screen(true);
		}

		if ((this->game_object->transform->getRotation() >= 350 && this->game_object->transform->getRotation() <= 360) ||
			(this->game_object->transform->getRotation() >= 0 && this->game_object->transform->getRotation() <= 10)) {

			this->enabled = false;
			this->show_end_screen(false);
		}
		else {
			this->game_object->enabled = false;
			this->show_end_screen(true);
		}
	}
	//litterally quit the entire game close engine
	else if (message == "Quit")
		DerpEngine::render_window->close();

	else if (message == "Restart")
		this->start();
}

void PlayerComponent::show_end_screen(const bool died) {
	if (died)
		Scene::find("Game Over Menu")->get_component<TextRenderer>()->set_string("Crashed!");
	else
		Scene::find("Game Over Menu")->get_component<TextRenderer>()->set_string("You Won!");

	Scene::find("Game Over Menu")->enabled = true;
	Scene::find("Quit Button")->enabled = true;
	Scene::find("Restart Button")->enabled = true;
}