#pragma once
#include "AGameObject.hpp"
#include "../Managers/GameObjectManager.hpp"
#include "../Components/EnemySwarmHandler.hpp"

class EGameObject : public AGameObject
{
public:
	EGameObject(std::string name);
	void initialize();
};

