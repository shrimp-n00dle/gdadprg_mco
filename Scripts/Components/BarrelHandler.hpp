#pragma once
#include "AComponent.hpp"
#include "../GameObjects/Poolables/GameObjectPool.hpp"
#include "../Managers/ObjectPoolHolder.hpp"
#include "../GameObjects/Poolables/Barrel.hpp"

class BarrelHandler : public AComponent
{
public:
	BarrelHandler(int numBarrels, std::string name, AGameObject* parent);
	~BarrelHandler();
	void perform();

	int getCounter();
	void setCounter(int increment);

private:
	int counter = 0;
	GameObjectPool* BarrelPool;
	const float SPAWN_INTERNAL = 0.01f;
	float ticks = 0.0f;
};

