#include "MusicComponent.hpp"

MusicComponent::MusicComponent() : music_object(), is_paused(false), is_playing(false) {}

void MusicComponent::load_music(std::string path) {
	this->music_object.openFromFile(path);
}

void MusicComponent::stop() {
	this->music_object.stop();
	this->is_playing = false;
	this->is_paused = false;
}

//if the object is playing restart it otherwise play it
void MusicComponent::play(bool restart) {
	if (this->is_playing)
		return;
	if (this->is_paused && restart) {
		this->music_object.play();
		this->is_paused = false;
		this->is_playing = true;
		return;
	}
	else if (this->is_paused && !restart)
		return;

	this->music_object.play();
	this->is_playing = true;
	this->is_paused = false;
}

void MusicComponent::pause() {
	if (this->is_paused)
		return;
	this->music_object.pause();
	this->is_paused = true;
	this->is_playing = false;
}