#pragma once
#include "../AComponent.hpp"
#include "unordered_map"
#include "../../GameObjects/Poolables/OilCan.hpp"
#include "../../Inputs/MCOPlayerInput.hpp"

#include "rapidjson-1.1.0/include/rapidjson/filereadstream.h"
#include "rapidjson-1.1.0/include/rapidjson/document.h"
#include "rapidjson-1.1.0/include/rapidjson/rapidjson.h"

//unordered map of string
typedef std::unordered_map<int, std::vector<int>> CList;

class CBehaviour : public AComponent
{
public:
	CBehaviour(std::string name);
	void perform();
private:
	std::vector<int> coord;
	sf::IntRect currSprite;
	int counter = 0;
	//read the sheets hre instead of sprite scene
	void initializeSprites();
	CList spriteList;
	std::vector<int> traverseList(int counter);
};

