#include "SoundComponent.hpp"

SoundComponent::SoundComponent() : audio_object(), sound_buffer(), is_playing(false){
	this->audio_object.setBuffer(this->sound_buffer);
}

void SoundComponent::load_sound(std::string path) {
	this->stop();
	this->sound_buffer.loadFromFile(path);
}

void SoundComponent::play() {
	this->audio_object.stop();
	this->audio_object.play();
	this->is_playing = true;
}

void SoundComponent::stop() {
	this->audio_object.stop();
	this->is_playing = false;
}