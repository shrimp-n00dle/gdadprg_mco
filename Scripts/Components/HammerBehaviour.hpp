#pragma once
#include "AComponent.hpp"
#include "../GameObjects/AGameObject.hpp"
#include "../Game.hpp"
#include "SFML/Graphics.hpp"

//unordered map of string
typedef std::unordered_map<int, std::vector<int>> HammerList;

class HammerBehaviour : public AComponent
{
public:
	HammerBehaviour(std::string name);
	void perform();
private:
	float ticks = 0.0f;
	float timer = 10.0f;
	std::vector<int> coord;
	sf::IntRect currSprite;
	int counter = 0;
	//read the sheets hre instead of sprite scene
	void initializeSprites();
	HammerList spriteList;
	std::vector<int> traverseList(int counter);

};



