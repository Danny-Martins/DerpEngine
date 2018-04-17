#pragma once

#include <SFML/Audio.hpp>
#include <TinyXML/tinyxml.h>

#include "Component.h"
#include "GameObject.h"

class MusicComponent : public Component {

	public:
		MusicComponent();
		//note this is engine start function not musiccomponent (see this->play)
		void start() override;

		void stop();
		void play(bool restart);
		void pause();
		void load_music(std::string path);

		static void set_component_from_xml(TiXmlElement* xml_element, GameObject* gameobject) {
			MusicComponent *music_component = new MusicComponent();
			std::string asset_path = xml_element->FirstChildElement()->GetText();
			music_component->load_music(asset_path);
			std::string play_on_start_string = xml_element->FirstChildElement()->NextSiblingElement()->GetText();
			if (play_on_start_string == "true")
				music_component->play_on_start = true;
			gameobject->add_component(music_component);
		}

	public:
		bool is_paused;
		bool is_playing;

	private:
		bool play_on_start;
		sf::Music music_object;

};