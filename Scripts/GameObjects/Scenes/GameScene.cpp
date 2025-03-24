#include "GameScene.hpp"


GameScene::GameScene() : AScene("GameScene") {}


void GameScene::onLoadResources() {}

void GameScene::onLoadObjects()
{
    BGameObject* bgObject = new BGameObject("BGameObject");
    this->registerObject(bgObject);

    AirplanePlayer* planeObject = new AirplanePlayer("PlaneObject");
    PhysicsManager::getInstance()->initialize("PlanePhysics", planeObject);
    this->registerObject(planeObject);

    AirplaneSupport* support1 = new AirplaneSupport("Airsupport1");
    planeObject->attachChild(support1);
    support1->setChildPosition(50, 100);
    //PhysicsManager::getInstance()->initialize("supportPhysics1", support1);

    AirplaneSupport* support2 = new AirplaneSupport("Airsupport2");
    planeObject->attachChild(support2);
    support2->setChildPosition(-50, 100);
    //PhysicsManager::getInstance()->initialize("supportPhysics2", support2);

    srand(time(nullptr));
    EGameObject* enemiesManager = new EGameObject("EnemiesManager");
    EnemySwarmHandler* swarmHandler = new EnemySwarmHandler(10, "SwarmHandler", enemiesManager);
    enemiesManager->attachComponent(swarmHandler);
    this->registerObject(enemiesManager);

    GameObjectPool* projectilePool = new GameObjectPool(ObjectPoolHolder::PROJECTILE_POOL_TAG, new ProjectileObject("projectile"), 10, nullptr);
    projectilePool->initialize();
    ObjectPoolHolder::getInstance()->registerObjectPool(projectilePool);

    /*UI*/
     MenuBar* barObject = new MenuBar("MenuBarScreen");
     this->registerObject(barObject);

     ReturnScreen* returnMenu = new ReturnScreen("ReturnScreen");
     this->registerObject(returnMenu);
     returnMenu->setEnabled(false);
}

void GameScene::onUnloadResources() {}
