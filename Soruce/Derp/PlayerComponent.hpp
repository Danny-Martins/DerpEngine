#pragma once

#include "Component.h"
#include "GameObject.h"

#include "TextRenderer.h"

class PlayerComponent : public Component {

	public:
		PlayerComponent();
		void start() override;
		void update(const float delta_time) override;

		static void create_component_from_xml(TiXmlElement* xml_element, GameObject* gameobject) {
			PlayerComponent *player_component = new PlayerComponent();
			xml_element = xml_element->FirstChildElement();
			player_component->thrust_power = std::stof(xml_element->GetText());
			xml_element = xml_element->NextSiblingElement();
			player_component->fuel_spend_amount = std::stof(xml_element->GetText());
			xml_element = xml_element->NextSiblingElement();
			player_component->remaining_fuel = std::stof(xml_element->GetText());
			xml_element = xml_element->NextSiblingElement();
			player_component->rotation_speed = std::stof(xml_element->GetText());
			gameobject->add_component(player_component);
		}

	private:
		void rotate(const float angle);
		void thrust();

		float thrust_power;
		float fuel_spend_amount;
		float remaining_fuel;

		float rotation_speed;

		TextRenderer *player_gui_fuel;
};