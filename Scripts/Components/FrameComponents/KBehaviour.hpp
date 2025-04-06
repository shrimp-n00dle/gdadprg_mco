#pragma once
#include "../AComponent.hpp"
#include "unordered_map"
#include "../../GameObjects/Poolables/Kong.hpp"

#include "rapidjson-1.1.0/include/rapidjson/filereadstream.h"
#include "rapidjson-1.1.0/include/rapidjson/document.h"
#include "rapidjson-1.1.0/include/rapidjson/rapidjson.h"

#include "../../GameObjects/EGameObject.hpp"
#include "../../Managers/SceneManager.hpp"


//unordered map of string
typedef std::unordered_map<int, std::vector<int>> KList;

class KBehaviour : public AComponent
{
public:
	KBehaviour(std::string name);
	void perform();
private:
	std::vector<int> coord;
	sf::IntRect currSprite;
	int counter = 0;
	//read the sheets hre instead of sprite scene
	void initializeSprites();
	KList spriteList;
	std::vector<int> traverseList(int counter);
};

