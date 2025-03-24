#pragma once
#include "AGameObject.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Components/BGMovement.hpp"
#include "../Inputs/BGInput.hpp"
#include "iostream"

class BGameObject : public AGameObject
{
public:
	BGameObject(std::string name);
	void initialize();
	void processInput(sf::Event event);

private:
	const float SPEED_MULTIPLIER = 100.0f;
};

