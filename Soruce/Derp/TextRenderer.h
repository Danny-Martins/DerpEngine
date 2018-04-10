#pragma once

#include <SFML/Graphics/Text.hpp>
#include "Component.h"

class TextRenderer : public Component {

	public:
		TextRenderer();
		void start() override;
		void update(float delta_time) override;

		void set_string(std::string new_text_string);

	public:
		sf::Vector2f offset;
		sf::Text text;

	private:
		sf::Font font;

};
