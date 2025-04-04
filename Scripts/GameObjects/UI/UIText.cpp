#include "UIText.hpp"
#include "sstream"

UIText::UIText(std::string name) : AGameObject(name)
{
	this->text = new sf::Text();
}

UIText::~UIText()
{
	delete this->text;
}

void UIText::initialize()
{
	//declare the a text to be used
	//font must be a pointner or else it get immesdiatly de alloacted
	std::cout << "Font declared as  " << this->getName() << std::endl;

	sf::Font* font = FontManager::getInstance()->getFont("nesfont");
	text->setFont(*font);
	text->setFillColor(sf::Color::White);
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(4.0f);
	this->setSize(40);
	this->setText("<Using placeholder!>");

	Renderer* renderer = new Renderer("Text");
	renderer->assignDrawable(text);
	this->attachComponent(renderer);
}

void UIText::setText(std::string text)
{
	this->text->setString(text);
	sf::FloatRect bounds = this->text->getLocalBounds();

	//align center you can put other alignement here
	this->text->setOrigin(bounds.width / 2, bounds.height / 2);
}

void UIText::setTextStyled(std::string text)
{
    // [Self-Made] Text Wrapping Function
    const sf::Font* font = this->text->getFont();
    if (!font) return;

    float maxWidth = 550.f;
    std::string wrappedText, currentLine, word;
    float spaceWidth = this->text->getCharacterSize() * 0.4f;

    std::istringstream stream(text);
    while (stream >> word) {
        std::string tempLine = currentLine.empty() ? word : currentLine + " " + word;

        sf::Text tempText(tempLine, *font, this->text->getCharacterSize());
        float lineWidth = tempText.findCharacterPos(tempLine.length()).x;

        if (lineWidth > maxWidth) {
            wrappedText += currentLine + "\n";  // Wrap line
            currentLine = word;  // Start new line
        }
        else {
            currentLine = tempLine;
        }
    }
    if (!currentLine.empty()) {
        wrappedText += currentLine;  // Add last line
    }

    this->text->setString(wrappedText);

    // this->text->setString(text);
    sf::FloatRect bounds = this->text->getLocalBounds();
    this->text->setOrigin(bounds.width / 2, bounds.height / 2);
}

std::string UIText::getText()
{
	return this->text->getString();
}

void UIText::setSize(unsigned int size)
{
	this->text->setCharacterSize(size);
}

void UIText::setColor(sf::Color color)
{
	this->text->setFillColor(color);
}
