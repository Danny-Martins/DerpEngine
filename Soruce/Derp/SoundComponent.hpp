#pragma once

#include <SFML/Audio.hpp>

#include "Component.h"

class SoundComponent : public Component {
	
	public:
		SoundComponent();

		void play();
		void stop();
		void load_sound(std::string path);

	public:
		bool is_playing;

	private:
		sf::SoundBuffer sound_buffer;
		sf::Sound audio_object;
};