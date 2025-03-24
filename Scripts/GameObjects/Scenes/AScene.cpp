#include "AScene.hpp"

AScene::AScene(std::string sceneName)
{
	this->sceneName = sceneName;
}

void AScene::onUnloadObjects()
{
	GameObjectManager::getInstance()->deleteAllObjectsInScene();
}

std::string AScene::getSceneName()
{
	return this->sceneName;
}

void AScene::registerObject(AGameObject* object)
{
	GameObjectManager::getInstance()->addObject(object);
}