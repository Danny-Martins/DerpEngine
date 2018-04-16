#pragma once
#include <SFML/Graphics.hpp>

#include "Component.h"
#include "SpriteRenderer.h"
#include <iostream>
#include <string>

class BoxCollider : public Component {

	public:
		static void set_component_from_xml(TiXmlElement* xml_element, GameObject* gameobject) {
			std::string boolean_string = xml_element->FirstChildElement()->GetText();
			//if use sprite
			if (boolean_string == "true") {
				std::cout << "in function" << std::endl;
				sf::Vector2f bounding_box;
				SpriteRenderer *sprite_renderer = gameobject->get_component<SpriteRenderer>();
				bounding_box.x = sprite_renderer->get_sprite().getGlobalBounds().width * (gameobject->transform->getScale().x * 0.5f);
				bounding_box.y = sprite_renderer->get_sprite().getGlobalBounds().height * (gameobject->transform->getScale().y * 0.5f);
				BoxCollider *box_collider = new BoxCollider(bounding_box.x, bounding_box.y);
				gameobject->add_component(box_collider);
				return;
			}
		}

		BoxCollider(float half_width, float half_height);
		void start() override;
		void update(float delta_time) override;


	public:
		sf::Vector2f bottom_left;
		sf::Vector2f top_right;

		float half_width;
		float half_height;

	private:
		bool draw_bounding_box;
		sf::RectangleShape bounding_box;
};