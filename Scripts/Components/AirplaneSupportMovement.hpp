#pragma once
#include "../Components/AComponent.hpp"
#include "../GameObjects/AGameObject.hpp"
#include "iostream"
#include "../GameObjects/AirplaneSupport.hpp"

class AirplaneSupportMovement : public AComponent
{
public:
	AirplaneSupportMovement(std::string name);
	void perform();
	bool moveRight = false;
	bool moveLeft = false;

private:
	const float SPEED_MULTIPLIER = 50.0f;
	bool bReturn = false;
};

