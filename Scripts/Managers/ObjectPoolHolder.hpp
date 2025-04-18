#pragma once
#include "../GameObjects/Poolables/GameObjectPool.hpp"
#include "unordered_map"

typedef std::unordered_map<std::string, GameObjectPool*> PoolMap;

class ObjectPoolHolder : sf::NonCopyable
{
public:
	static const std::string ENEMY_POOL_TAG;
	static const std::string PROJECTILE_POOL_TAG;
	static const std::string LADDER_POOL_TAG;
	static const std::string HAMMER_POOL_TAG;
	static const std::string BARREL_POOL_TAG;
	static const std::string PRINCESS_POOL_TAG;
	static const std::string KONG_POOL_TAG;
	static const std::string CAN_POOL_TAG;
	static const std::string FIRE_POOL_TAG;


	static ObjectPoolHolder* getInstance();

	void registerObjectPool(GameObjectPool* pool);
	void unregisterObjectPool(GameObjectPool* pool);
	GameObjectPool* getPool(std::string tag);

private:
	ObjectPoolHolder() {};

	static ObjectPoolHolder* sharedInstance;

	PoolMap poolMap;
};

