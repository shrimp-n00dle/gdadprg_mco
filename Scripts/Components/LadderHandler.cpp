#include "LadderHandler.hpp"


LadderHandler::LadderHandler(int numLadders, std::string name, AGameObject* parent) : AComponent(name, Script)
{
	/*Object pooling*/
	LadderPool = new GameObjectPool(ObjectPoolHolder::LADDER_POOL_TAG, new Ladder("ladder"), numLadders, parent);

	LadderPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(LadderPool);
}

LadderHandler::~LadderHandler()
{
	delete LadderPool;
}

void LadderHandler::perform()
{
	GameObjectPool* LadderPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::LADDER_POOL_TAG);
	ticks += deltaTime.asSeconds();

	if (ticks > SPAWN_INTERNAL)
	{
		//std::cout << "CHECK SPAWN " << std::endl;
		ticks = 0.0f;
		LadderPool->requestPoolable();
	}
}