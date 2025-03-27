#pragma once
#include "AComponent.hpp"
#include "../GameObjects/Poolables/GameObjectPool.hpp"
#include "../Managers/ObjectPoolHolder.hpp"
#include "../GameObjects/Poolables/Hammer.hpp"

class HammerHandler : public AComponent
{
public:
	HammerHandler(int numHammers, std::string name, AGameObject* parent);
	~HammerHandler();
	void perform();

private:
	GameObjectPool* HammerPool;
	const float SPAWN_INTERNAL = 0.01f;
	float ticks = 0.0f;
};

