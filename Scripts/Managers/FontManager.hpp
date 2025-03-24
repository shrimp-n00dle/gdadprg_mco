#pragma once
#include "SFML/Graphics.hpp"
#include "unordered_map"
#include "iostream"

class FontManager
{
public:
	static FontManager* getInstance();

	void loadAll();
	sf::Font* getFont(std::string);

private:

	//set constructor to private
	FontManager() {};

	//set copy constructor to private
	FontManager(FontManager const&) {};

	//assignment operator is private
	FontManager& operator=(FontManager const&) {};
	static FontManager* sharedInstance;

	void loadFont(std::string, std::string);
	std::unordered_map<std::string, sf::Font*> fontMap;
};

