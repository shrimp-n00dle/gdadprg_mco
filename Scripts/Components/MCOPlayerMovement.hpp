#pragma once
#include "AComponent.hpp"
#include "../GameObjects/Player.hpp"
#include "../GameObjects/Poolables/Ladder.hpp"
#include "../Inputs/MCOPlayerInput.hpp"
#include "../Managers/ObjectPoolHolder.hpp"
#include "SFML/Graphics.hpp"

class MCOPlayerMovement : public AComponent
{
public:
	MCOPlayerMovement(std::string name);
	void perform();
	bool bLadder = false;
private:
	float timer = 10.0f;
	const float SPEED_MULTIPLIER = 300.0f;
	const float BULLET_SPAWN_INTERVAL = 2.0f;
	float ticks = 0.0f;
	GameObjectPool* projectilePool;

};

