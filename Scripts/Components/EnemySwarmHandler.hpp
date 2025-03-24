#pragma once
#include "AComponent.hpp"
#include "../GameObjects/Poolables/GameObjectPool.hpp"
#include "../Managers/ObjectPoolHolder.hpp"
#include "../GameObjects/Poolables/EnemyAirplane.hpp"

class EnemySwarmHandler : public AComponent
{
public:
	EnemySwarmHandler(int numEnemies, std::string name, AGameObject* parent);
	~EnemySwarmHandler();
	void perform();

private:
	GameObjectPool* enemyPool;
	const float SPAWN_INTERNAL = 0.01f;
	float ticks = 0.0f;
};

