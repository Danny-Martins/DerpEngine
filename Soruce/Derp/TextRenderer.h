#pragma once

#include <SFML/Graphics/Text.hpp>
#include "Component.h"

#include "GameObject.h"
#include <TinyXML/tinyxml.h>

class TextRenderer : public Component {

	public:
		TextRenderer();
		void start() override;
		void update(float delta_time) override;

		void set_string(std::string new_text_string);
		void set_size(int new_size);

		static void create_component_from_xml(TiXmlElement* xml_element, GameObject* gameobject) {
			TextRenderer *text_renderer = new TextRenderer();
			text_renderer->set_string(xml_element->FirstChildElement()->GetText());
			text_renderer->set_size(std::stoi(xml_element->FirstChildElement()->NextSiblingElement()->GetText()));
			xml_element = xml_element->FirstChildElement()->NextSiblingElement()->NextSiblingElement();
			text_renderer->offset = sf::Vector2f(std::stof(xml_element->Attribute("x")), std::stof(xml_element->Attribute("y")));
			gameobject->add_component(text_renderer);
		}

	public:
		sf::Vector2f offset;
		sf::Text text;

	private:
		sf::Font font;

};
