#include "JScene.hpp"

JScene::JScene() : AScene("JanScene") {}

void JScene::onLoadResources() {}

void JScene::onLoadObjects()
{
	/*Player*/
	Player* player = new Player("player");
	PhysicsManager::getInstance()->initialize("PlayerPhysics", player);
	this->registerObject(player);

	/*Ladder*/
	srand(time(nullptr));
	EGameObject* ladderManager = new EGameObject("ladderManager");
	LadderHandler* ladderHandler = new LadderHandler(1, "ladderHandler", ladderManager);
	ladderManager->attachComponent(ladderHandler);
	this->registerObject(ladderManager);

	/*Hammer*/
	//srand(time(nullptr));
	//EGameObject* hammerManager = new EGameObject("HammerManager");
	//HammerHandler* hammerHandler = new HammerHandler(2, "HammerHandler", hammerManager);
	///hammerManager->attachComponent(hammerHandler);
	//this->registerObject(hammerManager);

	//AirplaneSupport* support2 = new AirplaneSupport("Airsupport2");
	//planeObject->attachChild(support2);
	//support2->setChildPosition(-50, 100);

	//QuitScreen* quitScreen = new QuitScreen("QuitScreen");
	//this->registerObject(quitScreen);
	//quitScreen->setEnabled(false);

}
void JScene::onUnloadResources() {}