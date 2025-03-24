#pragma once
#include "AComponent.hpp"
#include "../Managers/ObjectPoolHolder.hpp"
class ProjectileMovement : public AComponent
{
public:
	ProjectileMovement(std::string name);
	void perform();
	void reset();

private:

	const float SPEED_MULTIPLIER = 240.0f;
	float ticks = 0.0f;
};

