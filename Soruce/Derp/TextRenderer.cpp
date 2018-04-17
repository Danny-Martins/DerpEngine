#include "TextRenderer.h"
#include "DerpEngine.h"

TextRenderer::TextRenderer() : text(), font(), offset(0, 0) {
	this->font.loadFromFile("..\\Assets\\Fonts\\nasalization-rg.ttf");
	this->text.setFont(this->font);

	this->text.setString("New Text");
}

void TextRenderer::start() {
	sf::Vector2f calculated_origin;
	calculated_origin.x = this->text.getLocalBounds().left + (this->text.getLocalBounds().width / 2);
	calculated_origin.y = this->text.getLocalBounds().top + (this->text.getLocalBounds().height / 2);
	this->text.setOrigin(calculated_origin);
}

void TextRenderer::update(float delta_time) {
	DerpEngine::render_window->draw(this->text, this->game_object->get_world_transform().translate(this->offset));
}

void TextRenderer::set_string(std::string new_text_string) {
	this->text.setString(new_text_string);
}

void TextRenderer::set_size(int new_size) {
	this->text.setCharacterSize(new_size);
}