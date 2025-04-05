#include "BarrelHandler.hpp"

BarrelHandler::BarrelHandler(int numBarrels, std::string name, AGameObject* parent) : AComponent(name, Script)
{
	BarrelPool = new GameObjectPool(ObjectPoolHolder::BARREL_POOL_TAG, new Barrel("Barrel"), numBarrels, parent);

	BarrelPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(BarrelPool);
}

BarrelHandler::~BarrelHandler()
{
	delete BarrelPool;
}

void BarrelHandler::perform()
{
	GameObjectPool* BarrelPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::BARREL_POOL_TAG);
	ticks += deltaTime.asSeconds();

	if (ticks > SPAWN_INTERNAL)
	{
		ticks = 0.0f;
		BarrelPool->requestPoolable();
	}
}

int BarrelHandler::getCounter() { return counter; }

void BarrelHandler::setCounter(int increment) { counter += increment; }