#include "CHandler.hpp"

CHandler::CHandler(int numNPCs, std::string name, AGameObject* parent) : AComponent(name, Script)
{
	/*Object Pooling*/
	CPool = new GameObjectPool(ObjectPoolHolder::CAN_POOL_TAG, new OilCan("oilcan"), numNPCs, parent);
	CPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(CPool);
}

CHandler::~CHandler()
{
	delete CPool;
}

void CHandler::perform()
{
	GameObjectPool* PPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::CAN_POOL_TAG);
	ticks += deltaTime.asSeconds();

	if (ticks > SPAWN_INTERNAL)
	{
		ticks = 0.0f;
		PPool->requestPoolable();
	}
}