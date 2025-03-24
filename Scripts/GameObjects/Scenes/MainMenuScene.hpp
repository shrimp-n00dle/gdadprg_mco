#pragma once
#include "AScene.hpp"
#include "../UI/MainMenuScreen.hpp"

class MainMenuScene : public AScene
{
public:
	MainMenuScene();

	void onLoadResources();
	void onLoadObjects();

	void onUnloadResources();
};

