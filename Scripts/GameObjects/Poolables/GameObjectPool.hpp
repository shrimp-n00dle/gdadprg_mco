#pragma once
#include "../APoolable.hpp"
#include "../../Managers/GameObjectManager.hpp"
#include <vector>

class GameObjectPool
{
public: 
	int objCounter = 0;
	GameObjectPool(std::string tag, APoolable* poolableCopy, int poolableSize, AGameObject* parent);
	~GameObjectPool();
	void initialize();
	bool hasObjectAvailable(int requestSize);
	APoolable* requestPoolable();
	std::vector<APoolable*> requestPoolableBatch(int size);

	void releasePoolable(APoolable* poolableObject);
	void releasePoolableBatch(std::vector<APoolable*> objectList);

	std::string getTag();

private:
	std::string tag;
	APoolable* objectCopy = NULL;
	AGameObject* parent = NULL;
	int maxPoolSize = 1;
	std::vector<APoolable*> availableObjects;
	std::vector<APoolable*> usedObjects;

	void setEnabled(APoolable* poolableObject, bool flag);

};

