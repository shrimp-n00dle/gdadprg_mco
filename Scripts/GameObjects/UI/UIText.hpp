#pragma once
#include "../AGameObject.hpp"
#include "../../Managers/FontManager.hpp"
#include "string"

class UIText : public AGameObject
{
public:
	UIText(std::string name);
	~UIText();
	void initialize();
	void setText(std::string text);
	void setTextStyled(std::string text);
	std::string getText();
	void setFont(std::string key);
	void setSize(unsigned int size);
	void setColor(sf::Color color);
	void setOutlineColor(sf::Color color);
	void setOutlineThickness(int thicc);

private:
	sf::Text* text;
};

