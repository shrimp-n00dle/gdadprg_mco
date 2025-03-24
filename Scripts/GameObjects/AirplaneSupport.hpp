#pragma once
#include "AGameObject.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Components/AirplaneSupportMovement.hpp"

class AirplaneSupport : public AGameObject
{
public:
	AirplaneSupport(std::string name);
	void initialize();
	void processInput(sf::Event event);
};

