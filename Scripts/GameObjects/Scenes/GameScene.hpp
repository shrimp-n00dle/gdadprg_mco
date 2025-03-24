#pragma once
#include "AScene.hpp"
#include "../UI/GameScreen.hpp"
#include "../UI/ReturnScreen.hpp"

class GameScene : public AScene
{
public:
	GameScene();

	void onLoadResources();
	void onLoadObjects();

	void onUnloadResources();
};

