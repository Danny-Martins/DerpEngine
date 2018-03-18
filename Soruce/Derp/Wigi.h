#pragma once

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "SpriteRenderer.h"
#include "InputHandeler.hpp"
#include "Rigidbody.h"

//typedef void key_function();

class Wigi : public GameObject {

	public:
		Wigi();
		void rotate_left();
		void rotate_right();
		void thrust();
		virtual void update(float delta_time) override;

	private:
		float move_speed;
};
