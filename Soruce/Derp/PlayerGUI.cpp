#include "PlayerGUI.hpp"

PlayerGUI::PlayerGUI() : GameObject("Player GUI", nullptr){
	this->score = new TextRenderer();
	this->score->set_string("SCORE ERROR");
	this->transform->setPosition(125, 30);
	this->add_component(this->score);
}