#include "UIText.hpp"

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

	sf::Font* font = FontManager::getInstance()->getFont("default");
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

std::string UIText::getText()
{
	return this->text->getString();
}

void UIText::setSize(unsigned int size)
{
	this->text->setCharacterSize(size);
}