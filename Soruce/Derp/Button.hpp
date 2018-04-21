#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "TextRenderer.h"
#include "Component.h"

class Button : public Component {
	public:
		Button();

		void start() override;
		void update(float delta_time) override;

		static void create_component_from_xml(TiXmlElement* xml_element, GameObject* gameobject) {
			Button *button = new Button();
			xml_element = xml_element->FirstChildElement();
			sf::Vector2f box_size = sf::Vector2f(std::stof(xml_element->Attribute("x"))
												, std::stof(xml_element->Attribute("y")));
			button->width = box_size.x;
			button->height = box_size.y;

			xml_element = xml_element->NextSiblingElement();
			button->button_box.setOutlineThickness(std::stof(xml_element->GetText()));

			xml_element = xml_element->NextSiblingElement();
			button->normal_color = sf::Color( std::stof(xml_element->Attribute("x")), std::stof(xml_element->Attribute("y")), 
				std::stof(xml_element->Attribute("z")), std::stof(xml_element->Attribute("w")));

			xml_element = xml_element->NextSiblingElement();
			button->highlight_color = sf::Color(std::stof(xml_element->Attribute("x")), std::stof(xml_element->Attribute("y")),
				std::stof(xml_element->Attribute("z")), std::stof(xml_element->Attribute("w")));

			xml_element = xml_element->NextSiblingElement();
			button->message = xml_element->GetText();

			gameobject->add_component(button);
		}

	public:
		sf::RectangleShape button_box;
		float width, height;
		//bool is_mouse_hovered;

	private:
		sf::Color normal_color;
		sf::Color highlight_color;
		std::string message;
};
