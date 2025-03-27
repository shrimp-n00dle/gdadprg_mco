#pragma once
#include "AComponent.hpp"
#include "../GameObjects/Poolables/GameObjectPool.hpp"
#include "../Managers/ObjectPoolHolder.hpp"
#include "../GameObjects/Poolables/Ladder.hpp"

class LadderHandler : public AComponent
{
public:
	LadderHandler(int numLadders, std::string name, AGameObject* parent);
	~LadderHandler();
	void perform();

private:
	GameObjectPool* LadderPool;
	const float SPAWN_INTERNAL = 0.01f;
	float ticks = 0.0f;
};

