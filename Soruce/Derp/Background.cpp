#include "Background.hpp"
#include "SpriteRenderer.h"
#include "MusicComponent.hpp"

Background::Background() : GameObject("Background", nullptr) {

	GameObject* background = new GameObject("Background", nullptr);
	SpriteRenderer* background_sprite = new SpriteRenderer();
	background_sprite->set_sprite("..\\Assets\\Sprites\\Gameplay Background.png");
	background->add_component(background_sprite);
	background->transform->setPosition(sf::Vector2f(1280 / 2, 720 / 2));
	MusicComponent* background_music = new MusicComponent();
	background_music->load_music("..\\Assets\\Audio\\BGM\\Astrolander.wav");
	background_music->play(false);

}