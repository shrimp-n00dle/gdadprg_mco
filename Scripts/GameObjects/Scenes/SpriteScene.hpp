#pragma once
#include "AScene.hpp"
#include "../Frames/SpriteFrame.hpp"


class SpriteScene : public AScene
{
public:
	SpriteScene();

	void onLoadResources();
	void onLoadObjects();

	void onUnloadResources();
};

