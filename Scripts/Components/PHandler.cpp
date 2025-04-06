#include "PHandler.hpp"

PHandler::PHandler(int numNPCs, std::string name, AGameObject* parent) : AComponent(name, Script)
{
	/*Calls the pool obj*/
	PPool = new GameObjectPool(ObjectPoolHolder::PRINCESS_POOL_TAG, new Princess("princess"), numNPCs, parent);
	PPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(PPool);
}

PHandler::~PHandler()
{
	delete PPool;
}

void PHandler::perform()
{
	GameObjectPool* PPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::PRINCESS_POOL_TAG);
	ticks += deltaTime.asSeconds();

	if (ticks > SPAWN_INTERNAL)
	{
		ticks = 0.0f;
		PPool->requestPoolable();
	}
}