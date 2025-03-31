#pragma once
#include "AComponent.hpp"
#include "../GameObjects/AGameObject.hpp"
#include "../Game.hpp"
#include "SFML/Graphics.hpp"

class HammerBehaviour : public AComponent
{
public:
	HammerBehaviour(std::string name);
	void perform();
private:
	float ticks = 0.0f;
	float timer = 10.0f;

};

