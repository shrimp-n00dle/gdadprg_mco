#pragma once
#include "../AComponent.hpp"
#include "../../GameObjects/Frames/SpriteFrame.hpp"

#include "rapidjson-1.1.0/include/rapidjson/filereadstream.h"
#include "rapidjson-1.1.0/include/rapidjson/document.h"
#include "rapidjson-1.1.0/include/rapidjson/rapidjson.h"

//access the list like this for now
#include "../../GameObjects/Scenes/SpriteScene.hpp"


//unordered map of string
typedef std::unordered_map<int, std::vector<int>> SpriteList;

class FrameSwitcher : public AComponent
{
public:
	FrameSwitcher(std::string name);
	void perform();
private:
	std::vector<int> coord;
	//const float SPEED_MULTIPLIER = 100.0f;
	sf::IntRect currSprite;
	int counter = 0;
	//std::vector<std::string,std::vector<int>>

	//read the sheets hre instead of sprite scene
	void initializeSprites();

	SpriteList spriteList;

	std::vector<int> traverseList(int counter);

};

