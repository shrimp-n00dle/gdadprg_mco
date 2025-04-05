#include "NPCHandler.hpp"

NPCHandler::NPCHandler(int numNPCs, std::string name, AGameObject* parent) : AComponent(name, Script)
{
	NPCPool = new GameObjectPool(ObjectPoolHolder::PRINCESS_POOL_TAG, new Princess("princess"), numNPCs, parent);
	//NPCPool = new GameObjectPool(ObjectPoolHolder::Princess_POOL_TAG, new Princess("princess"), numNPCs, parent);
	NPCPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(NPCPool);
}

NPCHandler::~NPCHandler()
{
	delete NPCPool;
}

void NPCHandler::perform()
{
	GameObjectPool* NPCPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::PRINCESS_POOL_TAG);
	ticks += deltaTime.asSeconds();

	if (ticks > SPAWN_INTERNAL)
	{
		ticks = 0.0f;
		NPCPool->requestPoolable();
	}
}