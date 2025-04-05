#include "JScene.hpp"

JScene::JScene() : AScene("JanScene") {}

void JScene::onLoadResources() {}

void JScene::onLoadObjects()
{
	/*Level*/
	Level1Map* levelMap = new Level1Map("level1Map");
	Player* player = new Player("player");

	PhysicsManager::getInstance()->initialize("PlayerPhysics", player);

	/*Player*/
	this->registerObject(levelMap);
	this->registerObject(player);

	/*Ladder*/
	/*
	srand(time(nullptr));
	EGameObject* ladderManager = new EGameObject("ladderManager");
	LadderHandler* ladderHandler = new LadderHandler(1, "ladderHandler", ladderManager);
	ladderManager->attachComponent(ladderHandler);
	this->registerObject(ladderManager);
	*/

	/*Barrel*/
	srand(time(nullptr));
	EGameObject* barrelManager = new EGameObject("BarrelManager");
	BarrelHandler* barrelHandler = new BarrelHandler(1, "BarrelHandler", barrelManager);
	barrelManager->attachComponent(barrelHandler);
	this->registerObject(barrelManager);

	/*Barrel Checker*/
	Checker* checker = new Checker("Checker1");
	/*sprite->setPosition(platformBounds[i].left, platformBounds[i].top);*/
	//sprite->setSize(sf::Vector2f(platformBounds[i].width, platformBounds[i].height));
	checker->setChildPosition(750,250);
	this->registerObject(checker);

	Checker* checker2 = new Checker("Checker2");
	checker2->setChildPosition(350, 300);
	this->registerObject(checker2);

	Checker* checker3 = new Checker("Checker1");
	checker3->setChildPosition(20, 350);
	this->registerObject(checker3);

	//Checker* checker3 = new Checker("Checker");
	//checker3->setChildPosition(600, 250);
	//this->registerObject(checker3);

	//Checker* checker4 = new Checker("Checker");
	//checker4->setChildPosition(600, 250);
	//this->registerObject(checker4);

	//Checker* checker5 = new Checker("Checker");
	//checker4->setChildPosition(600, 250);
	//this->registerObject(checker4);
	
	/*Hammer*/
	srand(time(nullptr));
	EGameObject* hammerManager = new EGameObject("HammerManager");
	HammerHandler* hammerHandler = new HammerHandler(1, "HammerHandler", hammerManager);
	hammerManager->attachComponent(hammerHandler);
	this->registerObject(hammerManager);

	/*UI*/
	Level1UI* level1UI = new Level1UI("Level1UI");
	this->registerObject(level1UI);

	/*Princess, DonkeyKong and OilCan*/
	srand(time(nullptr));
	EGameObject* pManager = new EGameObject("PManager");
	PHandler* pHandler = new PHandler(1, "PHandler", pManager);
	pManager->attachComponent(pHandler);
	this->registerObject(pManager);

	srand(time(nullptr));
	EGameObject* kManager = new EGameObject("KManager");
	KHandler* kHandler = new KHandler(1, "KHandler", kManager);
	kManager->attachComponent(kHandler);
	this->registerObject(kManager);

	srand(time(nullptr));
	EGameObject* cManager = new EGameObject("CManager");
	CHandler* cHandler = new CHandler(1, "CHandler", cManager);
	cManager->attachComponent(cHandler);
	this->registerObject(cManager);

	//QuitScreen* quitScreen = new QuitScreen("QuitScreen");
	//this->registerObject(quitScreen);
	//quitScreen->setEnabled(false);

}
void JScene::onUnloadResources() {}