#pragma once

class Component
{
public:
	virtual void start() = 0;
	virtual void update(float delta_time) = 0;
};
