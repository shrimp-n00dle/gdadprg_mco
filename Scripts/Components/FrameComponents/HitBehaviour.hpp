#pragma once
#include "../AComponent.hpp"
#include "../../GameObjects/Player.hpp"
#include "../../Inputs/MCOPlayerInput.hpp"

#include "rapidjson-1.1.0/include/rapidjson/filereadstream.h"
#include "rapidjson-1.1.0/include/rapidjson/document.h"
#include "rapidjson-1.1.0/include/rapidjson/rapidjson.h"

//unordered map of string
typedef std::unordered_map<int, std::vector<int>> HitList;

class HitBehaviour : public AComponent
{
public:
	HitBehaviour(std::string name);
	void perform();
private:
	std::vector<int> coord;
	sf::IntRect currSprite;
	int counter = 0;
	int loop = 0;
	//read the sheets hre instead of sprite scene
	void initializeSprites();
	HitList spriteList;
	std::vector<int> traverseList(int counter);
};

