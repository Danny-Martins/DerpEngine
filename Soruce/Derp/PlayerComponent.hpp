#pragma

#include "Component.h"
#include "GameObject.h"

#include "TextRenderer.h"
#include "Rigidbody.h"

class PlayerComponent : public Component {

	public:
		PlayerComponent();
		void start() override;
		void update(const float delta_time) override;
		void recive_message(const std::string message) override;

		static void create_component_from_xml(TiXmlElement* xml_element, GameObject* gameobject) {
			PlayerComponent *player_component = new PlayerComponent();
			xml_element = xml_element->FirstChildElement();
			player_component->thrust_power = std::stof(xml_element->GetText());
			xml_element = xml_element->NextSiblingElement();
			player_component->fuel_spend_amount = std::stof(xml_element->GetText());
			xml_element = xml_element->NextSiblingElement();
			player_component->max_fuel = std::stof(xml_element->GetText());
			xml_element = xml_element->NextSiblingElement();
			player_component->rotation_speed = std::stof(xml_element->GetText());

			player_component->start_position = gameobject->transform->getPosition();
			gameobject->add_component(player_component);
		}

	private:
		void rotate(const float angle);
		void thrust();
		void show_end_screen(const bool died);

	private:

		std::string player_name;

		sf::Vector2f start_position;

		float thrust_power;
		float fuel_spend_amount;
		float max_fuel, remaining_fuel;

		float rotation_speed;

		TextRenderer *player_gui_fuel;
		Rigidbody *rigid_body;

		//if x or y velocity is greater than this its a crash
		const float crash_velocity_threshold;
};