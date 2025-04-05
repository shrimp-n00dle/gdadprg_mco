#pragma once
#include "AComponent.hpp"
#include "../GameObjects/Poolables/GameObjectPool.hpp"
#include "../Managers/ObjectPoolHolder.hpp"
#include "../GameObjects/Poolables/Princess.hpp"
#include "../GameObjects/Poolables/Kong.hpp"

class KHandler : public AComponent
{
public:
	KHandler(int numNPCs, std::string name, AGameObject* parent);
	~KHandler();
	void perform();

private:
	GameObjectPool* KPool;
	const float SPAWN_INTERNAL = 0.01f;
	float ticks = 0.0f;
};

