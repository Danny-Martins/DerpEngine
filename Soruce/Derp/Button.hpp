#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "TextRenderer.h"
#include "Component.h"

class Button : public Component {
	public:
		Button();

		void start() override;
		void update(float delta_time) override;

	public:
		TextRenderer* text;
		sf::RectangleShape button_box;
		bool is_mouse_hovered;
};
