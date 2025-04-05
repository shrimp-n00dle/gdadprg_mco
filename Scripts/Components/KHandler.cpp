#include "KHandler.hpp"

KHandler::KHandler(int numNPCs, std::string name, AGameObject* parent) : AComponent(name, Script)
{
	KPool = new GameObjectPool(ObjectPoolHolder::KONG_POOL_TAG, new Kong("kong"), numNPCs, parent);
	KPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(KPool);
}

KHandler::~KHandler()
{
	delete KPool;
}

void KHandler::perform()
{
	GameObjectPool* KPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::KONG_POOL_TAG);
	ticks += deltaTime.asSeconds();

	if (ticks > SPAWN_INTERNAL)
	{
		ticks = 0.0f;
		KPool->requestPoolable();
	}
}