#include "ObjectPoolHolder.hpp"

const std::string ObjectPoolHolder::ENEMY_POOL_TAG = "EnemyPool";

const std::string ObjectPoolHolder::PROJECTILE_POOL_TAG = "ProjectilePool";

const std::string ObjectPoolHolder::LADDER_POOL_TAG = "LadderPool";

const std::string ObjectPoolHolder::HAMMER_POOL_TAG = "HammerPool";

const std::string ObjectPoolHolder::BARREL_POOL_TAG = "BarrelPool";

const std::string ObjectPoolHolder::PRINCESS_POOL_TAG = "PrincessPool";

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





