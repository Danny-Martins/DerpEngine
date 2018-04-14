#pragma once

#include "GameObject.h"
#include "TextRenderer.h"

class PlayerGUI : public GameObject {
	public:
		PlayerGUI();
		void update_gui(unsigned int score, float remaining_fuel);

	private:
		TextRenderer *score;
};