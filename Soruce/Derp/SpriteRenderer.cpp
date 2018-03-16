#include "SpriteRenderer.h"
#include "DerpEngine.h"
#include <iostream>

void SpriteRenderer::start() {
	//
}

void SpriteRenderer::update(float delta_time) {

	DerpEngine::render_window->draw(this->sprite);
}

void SpriteRenderer::set_sprite(std::string image_path) {
	this->sprite_texture.loadFromFile(image_path);
	this->sprite.setTexture(this->sprite_texture);
}