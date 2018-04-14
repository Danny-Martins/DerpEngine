#pragma once

#include "GameObject.h"

class Lander : public GameObject {

	public:
		Lander();
		void rotate(float scalar);
		void thrust();

		virtual void start() override;
		virtual void update(float delta_time) override;

	private:
		float thrust_power;

};
