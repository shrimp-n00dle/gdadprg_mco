#include "JScene.hpp"

JScene::JScene() : AScene("JanScene") {}

void JScene::onLoadResources() {}

void JScene::onLoadObjects()
{
	ApplicationManager::getInstance()->resumeApplication();
	ScoreManager::getInstance()->resetBonusScore();
	ScoreManager::getInstance()->resetScore();

	/*Level*/
	Level1Map* levelMap = new Level1Map("level1Map");
	Player* player = new Player("player");

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
	

	/*Barrel*/
	srand(time(nullptr));
	EGameObject* barrelManager = new EGameObject("BarrelManager");
	BarrelHandler* barrelHandler = new BarrelHandler(1, "BarrelHandler", barrelManager);
	barrelManager->attachComponent(barrelHandler);
	this->registerObject(barrelManager);
	
	/*Hammer*/
	srand(time(nullptr));
	EGameObject* hammerManager = new EGameObject("HammerManager");
	HammerHandler* hammerHandler = new HammerHandler(1, "HammerHandler", hammerManager);
	hammerManager->attachComponent(hammerHandler);
	this->registerObject(hammerManager);

	/*UI*/
	Level1UI* level1UI = new Level1UI("Level1UI");
	this->registerObject(level1UI);

	/*Princess and DonkeyDong*/
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

	/*Goal*/
	Goal* goal = new Goal("Goal");
	this->registerObject(goal);

	PauseScreen* pauseScreen = new PauseScreen("PauseScreen");
	this->registerObject(pauseScreen);
	pauseScreen->setEnabled(false);

	// Main cause of the delayed scoring issue.
	// This is already initialized at the start, so any updates to scores are basically useless.
	ResultScreen* resultScreen = new ResultScreen("ResultScreen");
	this->registerObject(resultScreen);
	resultScreen->setEnabled(false);
	

	//QuitScreen* quitScreen = new QuitScreen("QuitScreen");
	//this->registerObject(quitScreen);
	//quitScreen->setEnabled(false);

}
void JScene::onUnloadResources() {}