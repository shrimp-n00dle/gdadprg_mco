#pragma once
#include "AComponent.hpp"
#include "../GameObjects/Poolables/GameObjectPool.hpp"
#include "../Managers/ObjectPoolHolder.hpp"
#include "../GameObjects/Poolables/Princess.hpp"

class NPCHandler : public AComponent
{
public:
	NPCHandler(int numNPCs, std::string name, AGameObject* parent);
	~NPCHandler();
	void perform();

private:
	GameObjectPool* NPCPool;
	const float SPAWN_INTERNAL = 0.01f;
	float ticks = 0.0f;
};

