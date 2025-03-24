#pragma once
#include "AComponent.hpp"
#include "../GameObjects/AGameObject.hpp"
#include "../Game.hpp"
#include "SFML/Graphics.hpp"

class EnemyBehaviour : public AComponent
{
public:
	enum EnemyMovementType {Delay = 0, Forward = 1, SlowForward = 2, Side = 3};

	EnemyBehaviour(std::string name);
	void perform();
	void configure(float delay);
	void reset();

private:
	const float SPEED_MULTIPLIER = 100.0f;
	EnemyBehaviour::EnemyMovementType movementType = Forward;
	float ticks = 0.0f;
	float delay = 0.0f;
	float forwardDuration = 0.0f;
};

