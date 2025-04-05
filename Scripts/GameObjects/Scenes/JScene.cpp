#include "JScene.hpp"

JScene::JScene() : AScene("JanScene") {}

void JScene::onLoadResources() {}

void JScene::onLoadObjects()
{
	/*Level*/
	Player* player = new Player("player");
	Level1Map* levelMap = new Level1Map("level1Map");

	PhysicsManager::getInstance()->initialize("PlayerPhysics", player);

	/*Player*/
	this->registerObject(levelMap);
	this->registerObject(player);

	/*Ladder*/
	srand(time(nullptr));
	EGameObject* ladderManager = new EGameObject("ladderManager");
	LadderHandler* ladderHandler = new LadderHandler(1, "ladderHandler", ladderManager);
	ladderManager->attachComponent(ladderHandler);
	this->registerObject(ladderManager);
	
	/*Hammer*/
	srand(time(nullptr));
	EGameObject* hammerManager = new EGameObject("HammerManager");
	HammerHandler* hammerHandler = new HammerHandler(2, "HammerHandler", hammerManager);
	hammerManager->attachComponent(hammerHandler);
	this->registerObject(hammerManager);

	/*Barrel*/
	srand(time(nullptr));
	EGameObject* barrelManager = new EGameObject("BarrelManager");
	BarrelHandler* barrelHandler = new BarrelHandler(1, "BarrelHandler", barrelManager);
	barrelManager->attachComponent(barrelHandler);
	this->registerObject(barrelManager);

	/*Donkey Kong and Princess*/
	/*srand(time(nullptr));
	EGameObject* npcManager = new EGameObject("NPCManager");
	NPCHandler* NPCHandler = new NPCHandler(1, "NPCHandler", NPCManager);
	NPCManager->attachComponent(NPCHandler);
	this->registerObject(NPCManager);*/


	//QuitScreen* quitScreen = new QuitScreen("QuitScreen");
	//this->registerObject(quitScreen);
	//quitScreen->setEnabled(false);

}
void JScene::onUnloadResources() {}