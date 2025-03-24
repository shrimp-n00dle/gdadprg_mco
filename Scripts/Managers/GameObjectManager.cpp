 #include "GameObjectManager.hpp"

 GameObjectManager* GameObjectManager::sharedInstance = nullptr;

 GameObjectManager* GameObjectManager::getInstance()
 {
     if (sharedInstance == nullptr)
     {
         sharedInstance = new GameObjectManager();
     }

     return sharedInstance;
 }

 AGameObject* GameObjectManager::findObjectByName(std::string name)
 {
     if (mGameObjectMap[name] != nullptr)
     {
         return mGameObjectMap[name];
     } else 
     {
         std::cout << name << " not found" << std::endl;
         return nullptr;
     }
 }

std::vector<AGameObject*> GameObjectManager::getAllObjects()
 {
     return mGameObjectList;
 }

 int GameObjectManager::activeObjects()
 {
     return (int)mGameObjectList.size();
 }
 
 void GameObjectManager::processInput(sf::Event event)
 {
     for (int i = 0; i < mGameObjectList.size() ; i++)
     {
         mGameObjectList[i]->processInput(event); 
     }
 }

 void GameObjectManager::update(sf::Time deltaTime)
 {
     for (int i = 0; i < mGameObjectList.size() ; i++)
     {
         mGameObjectList[i]->update(deltaTime); 
     }
 }


 void GameObjectManager::draw(sf::RenderWindow* window)
 {
     for (int i = 0; i < mGameObjectList.size() ; i++)
     {
         mGameObjectList[i]->draw(window, sf::RenderStates::Default); 
     }
 }

 void GameObjectManager::addObject(AGameObject* gameObject)
 {
     mGameObjectMap[gameObject->getName()] = gameObject;
     mGameObjectList.push_back(gameObject);
     gameObject->initialize();
 }

 void GameObjectManager::deleteObject(AGameObject* gameObject)
 {
     std::string key = gameObject->getName();
     delete gameObject;
     mGameObjectMap.erase(key);
     mGameObjectList.erase(std::remove(mGameObjectList.begin(),mGameObjectList.end(), gameObject));
     mGameObjectList.shrink_to_fit();
 }

 void GameObjectManager::deleteObjectByName(std::string name)
 {
     AGameObject* object = findObjectByName(name);

     if (object != nullptr)
     {
         deleteObject(object);
     }
 }

 void GameObjectManager::deleteAllObjectsInScene()
 {
     for (int i = 0; i < this->mGameObjectList.size(); i++)
     {
         delete this->mGameObjectList[i];
     }

     this->mGameObjectList.clear();
     this->mGameObjectList.shrink_to_fit();
     this->mGameObjectMap.clear();
 }