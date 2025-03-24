#pragma once
#include "AComponent.hpp"
#include "../GameObjects/AirplanePlayer.hpp"
#include "../Inputs/PlayerInput.hpp"
#include "../Managers/ObjectPoolHolder.hpp"
#include "SFML/Graphics.hpp"

class PlayerMovement : public AComponent
{
public:
	PlayerMovement(std::string name);
	void perform();
private:

	const float SPEED_MULTIPLIER = 300.0f;
	const float BULLET_SPAWN_INTERVAL = 2.0f;
	float ticks = 0.0f;
	GameObjectPool* projectilePool;

};

