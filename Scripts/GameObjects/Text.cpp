#include "Text.hpp"

Text::Text() {
   // mText.setColor(sf::Color::White);
    mText.setCharacterSize(30);
    mText.setStyle(sf::Text::Regular);
    mText.setString("hello");
    mText.setPosition(10.0f,10.0f);
}

void Text::setFont(sf::Font font)
{
    mFont = font;
    mText.setFont(mFont);
}

sf::Text* Text::getText()
{
    return &mText;
}
