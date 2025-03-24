#include "ObjectPoolHolder.hpp"

const std::string ObjectPoolHolder::ENEMY_POOL_TAG = "EnemyPool";

const std::string ObjectPoolHolder::PROJECTILE_POOL_TAG = "ProjectilePool";

ObjectPoolHolder* ObjectPoolHolder::sharedInstance = nullptr;

ObjectPoolHolder* ObjectPoolHolder::getInstance()
{
	if (sharedInstance == nullptr)
	{
		sharedInstance = new ObjectPoolHolder();
	}
	return sharedInstance;
}

void ObjectPoolHolder::registerObjectPool(GameObjectPool* pool)
{
	poolMap[pool->getTag()] = pool;
}

void ObjectPoolHolder::unregisterObjectPool(GameObjectPool* pool)
{
	poolMap.erase(pool->getTag());
	delete pool;
}

GameObjectPool* ObjectPoolHolder::getPool(std::string tag)
{
	return poolMap[tag];
}





