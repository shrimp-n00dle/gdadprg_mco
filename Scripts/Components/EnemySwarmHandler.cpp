#include "EnemySwarmHandler.hpp"


EnemySwarmHandler::EnemySwarmHandler(int numEnemies, std::string name, AGameObject* parent) : AComponent(name, Script)
{
	enemyPool = new GameObjectPool(ObjectPoolHolder::ENEMY_POOL_TAG, new EnemyAirplane("enemy"), numEnemies, parent);

	enemyPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(enemyPool);
}

EnemySwarmHandler::~EnemySwarmHandler()
{
	delete enemyPool;
}

void EnemySwarmHandler::perform()
{
	GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG);
	ticks += deltaTime.asSeconds();

	if (ticks > SPAWN_INTERNAL)
	{
		//std::cout << "CHECK SPAWN " << std::endl;
		ticks = 0.0f;
		enemyPool->requestPoolable();
	}
}