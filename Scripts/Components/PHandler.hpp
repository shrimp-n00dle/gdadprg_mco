#pragma once
#include "AComponent.hpp"
#include "../GameObjects/Poolables/GameObjectPool.hpp"
#include "../Managers/ObjectPoolHolder.hpp"
#include "../GameObjects/Poolables/Princess.hpp"
#include "../GameObjects/Poolables/Kong.hpp"

class PHandler : public AComponent
{
public:
	PHandler(int numNPCs, std::string name, AGameObject* parent);
	~PHandler();
	void perform();

private:
	GameObjectPool* PPool;
	const float SPAWN_INTERNAL = 0.01f;
	float ticks = 0.0f;
};

