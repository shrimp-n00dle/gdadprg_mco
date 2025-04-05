#pragma once
#include "AComponent.hpp"
#include "../GameObjects/Poolables/GameObjectPool.hpp"
#include "../Managers/ObjectPoolHolder.hpp"
#include "../GameObjects/Poolables/OilCan.hpp"

class CHandler : public AComponent
{
public:
	CHandler(int numNPCs, std::string name, AGameObject* parent);
	~CHandler();
	void perform();

private:
	GameObjectPool* CPool;
	const float SPAWN_INTERNAL = 0.01f;
	float ticks = 0.0f;
};
