#pragma once

#include <SFML/Graphics.hpp>

#include "Component.h"
#include "GameObject.h"

#include <TinyXML/tinyxml.h>

class SpriteRenderer : public Component {

	public:

		static void set_component_from_xml(TiXmlElement *xml_element, GameObject *gameobject) {
			SpriteRenderer *sprite_renderer = new SpriteRenderer();
			sprite_renderer->set_sprite(xml_element->FirstChildElement()->GetText());
			gameobject->add_component(sprite_renderer);
		}

		void start() override;
		void update(float delta_time) override;
		void set_sprite(std::string image_path);
		sf::Sprite get_sprite();

	private:
		sf::Sprite sprite;
		sf::Texture sprite_texture;
};