#pragma once
#include "AComponent.hpp"
#include "../GameObjects/BGameObject.hpp"
#include "../Inputs/BGInput.hpp"

//class BGameObject;

class BGMovement : public AComponent
{
public:
	BGMovement(std::string name);
	void perform();
private:
	const float SPEED_MULTIPLIER = 100.0f;
	
};

