#include "MainMenuScene.hpp"

MainMenuScene::MainMenuScene() : AScene("MainMenuScene")
{

}


void MainMenuScene::onLoadResources()
{
	
}

void MainMenuScene::onLoadObjects()
{
	MainMenuScreen* menuScene = new MainMenuScreen("MainMenuScreen");
	this->registerObject(menuScene);

	QuitScreen* quitScreen = new QuitScreen("QuitScreen");
	this->registerObject(quitScreen);
	quitScreen->setEnabled(false);
}

void MainMenuScene::onUnloadResources() {}