#pragma once

#include "Component.h"
#include <SFML/Audio.hpp>

class MusicComponent : public Component {

	public:
		MusicComponent();
		void stop();
		void play(bool restart);
		void pause();
		void load_music(std::string path);

	public:
		bool is_paused;
		bool is_playing;

	private:
		sf::Music music_object;

};