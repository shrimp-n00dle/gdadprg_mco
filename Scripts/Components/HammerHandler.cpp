#include "HammerHandler.hpp"

HammerHandler::HammerHandler(int numHammers, std::string name, AGameObject* parent) : AComponent(name, Script)
{
	/*Object Pooling*/
	HammerPool = new GameObjectPool(ObjectPoolHolder::HAMMER_POOL_TAG, new Hammer("hammer"), numHammers, parent);


	HammerPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(HammerPool);


}

HammerHandler::~HammerHandler()
{
	delete HammerPool;
}

void HammerHandler::perform()
{
	GameObjectPool* HammerPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::HAMMER_POOL_TAG);
	ticks += deltaTime.asSeconds();

	if (ticks > SPAWN_INTERNAL)
	{
		ticks = 0.0f;
		HammerPool->requestPoolable();
	}
}

int HammerHandler::getCounter() { return counter; }

void HammerHandler::setCounter(int increment) { counter += increment; }