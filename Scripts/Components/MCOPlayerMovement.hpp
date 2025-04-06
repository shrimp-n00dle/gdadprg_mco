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
	bool bHop = false;

private:
	float timer = 10.0f;
	float jumpTimer = 0.5f;
	const float SPEED_MULTIPLIER = 300.0f;
	const float JUMP_MULTIPLIER = 4.0f;
	float ticks = 0.0f;

	bool bHasHit = false;
	float hitDelay = 0.0f;
	const float HIT_SOUND_DURATION = 3.0f; // Adjust based on your hit sound length
	GameObjectPool* projectilePool;
};

