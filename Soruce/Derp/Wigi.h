#pragma once

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "SpriteRenderer.h"
#include "InputHandeler.hpp"

typedef void key_function();

class Wigi : GameObject {

	public:
		Wigi();
		~Wigi();
		void rotate_left();
		void rotate_right();
		void thrust();



};
