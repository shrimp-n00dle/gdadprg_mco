#include "HammerHandler.hpp"


HammerHandler::HammerHandler(int numHammers, std::string name, AGameObject* parent) : AComponent(name, Script)
{
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
		//std::cout << "CHECK SPAWN " << std::endl;
		ticks = 0.0f;
		HammerPool->requestPoolable();
	}
}