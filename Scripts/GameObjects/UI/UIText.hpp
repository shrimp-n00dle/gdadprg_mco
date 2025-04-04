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
	void setSize(unsigned int size);
	void setColor(sf::Color color);

private:
	sf::Text* text;
};

