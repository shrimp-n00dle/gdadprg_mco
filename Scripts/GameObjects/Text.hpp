#pragma once
#include "SFML/Graphics.hpp"

class Text
{
public:
    Text();
    void setFont(sf::Font font);
    sf::Text* getText();

private:
    sf::Font mFont;
    sf::Text mText;
};
