#pragma once

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Rigidbody.h"
#include "Debug.hpp"
#include "InputHandeler.hpp"

//typedef void key_function();

class Wigi : public GameObject {

	public:
		Wigi();
		void rotate_left();
		void rotate_right();
		void thrust();
		virtual void update(float delta_time) override;

		inline void setup_input() {
			InputHandler* input_handler = new InputHandler();
			input_handler->add_binding(sf::Keyboard::A, Wigi::derp);
			this->add_component(input_handler);
		}

		static void derp() {
			Debug::print("It worked!");
		}


	
		//void *Wigi::derp() {}

	private:
		Rigidbody* rigid_body;
		float move_speed;
};
