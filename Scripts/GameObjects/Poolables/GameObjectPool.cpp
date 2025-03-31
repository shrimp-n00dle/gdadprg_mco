#include "GameObjectPool.hpp"

GameObjectPool::GameObjectPool(std::string tag, APoolable* poolableCopy, int poolableSize, AGameObject* parent) 
{
	this->tag = tag;
	objectCopy = poolableCopy;
	maxPoolSize = poolableSize;
	this->parent = parent;
}

GameObjectPool::~GameObjectPool()
{
	delete objectCopy;
	objectCopy = nullptr;
	parent = nullptr;
}

void GameObjectPool::initialize()
{
	for (int i = 0; i < maxPoolSize; i++)
	{
		APoolable* poolableObj = objectCopy->clone();

		if (parent != nullptr)
		{
			parent->attachChild(poolableObj);
		}
		else
		{
			GameObjectManager::getInstance()->addObject(poolableObj);
		}

		poolableObj->setEnabled(false);
		availableObjects.push_back(poolableObj);
	}
}

bool GameObjectPool::hasObjectAvailable(int requestSize)
{
	return requestSize <= availableObjects.size();
}


APoolable* GameObjectPool::requestPoolable()
{
	if (hasObjectAvailable(1))
	{
		APoolable* poolableObj = availableObjects[availableObjects.size() - 1];
		availableObjects.erase(availableObjects.begin() + availableObjects.size() - 1);
		usedObjects.push_back(poolableObj);
		//std::cout << "Requested object Available: " << availableObjects.size() << " Used: " << usedObjects.size() << std::endl;
		setEnabled(poolableObj, true);
		return poolableObj;
	}

	else
	{
		//std::cerr << "No more poolable " << objectCopy->getName() << " available!" << std::endl;
		return NULL;
	}
}


std::vector<APoolable*> GameObjectPool::requestPoolableBatch(int size)
{
	std::vector<APoolable*> returnList;

	if (hasObjectAvailable(size))
	{
		for (int i = 0; i < size; i++)
		{
			returnList.push_back(requestPoolable());
		}
	}
	else
	{
		std::cerr << " Insufficient " << objectCopy->getName() << " available in pool." << "Count is: " <<
			availableObjects.size() << " while request is " << size << std::endl;
	}

	return returnList;
}

/*search for the list of currentused ibj in usedObjects then move 
that obj to availableObjects list while setting the corresponding flags*/
void GameObjectPool::releasePoolable(APoolable* poolableObject)
{
	// Search for the list of current used object in usedObjects then move that object to availableObjects list while setting the corresponding enabled flags

	int index = -1;

	for (int i = 0; i < this->usedObjects.size() && index == -1; i++) {
		if (this->usedObjects[i] == poolableObject)
			index = i;
	}

	if (index != -1) {
		this->availableObjects.push_back(poolableObject);
		this->usedObjects.erase(this->usedObjects.begin() + index);
		this->setEnabled(poolableObject, false);
	}
		//if (objCounter > 200) return;

		//	poolableObject->setEnabled(false);
		//	availableObjects.push_back(poolableObject);
			//usedObjects.erase(poolableObject);
		//	std::cout << this->objCounter << std::endl;
		//	this->objCounter++;
}

/*implement loop that will release list of objects*/
void GameObjectPool::releasePoolableBatch(std::vector<APoolable*> objectList)
{
	//the number of pools being release as it hits 30 is not consistent
	for (int i = 0; i < objectList.size(); i++)
	{
		//objectList[i]->onRelease();
		this->releasePoolable(objectList[i]);
		std::cout << "Released "  <<i << std::endl;
	}
	
	
}

std::string GameObjectPool::getTag()
{
	return tag;
}

void GameObjectPool::setEnabled(APoolable* poolableObj, bool flag)
{
	if (flag)
	{
		poolableObj->setEnabled(true);
		poolableObj->onActivate();
	}
	else
	{
		poolableObj->setEnabled(false);
		poolableObj->onRelease();
	}
}
