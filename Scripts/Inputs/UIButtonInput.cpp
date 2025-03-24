#include "UIButtonInput.hpp"

UIButtonInput::UIButtonInput(std::string name, ButtonListener* buttonListener) : GenericInput(name)
{
	this->buttonListener = buttonListener;
}

UIButtonInput::~UIButtonInput() 
{
	GenericInput::~GenericInput();
}

void UIButtonInput::perform()
{

	UIButton* button = (UIButton*)this->getOwner();
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && this->pressed)
	{
		this->pressed = false;
		button->changeButtonToNormal();
		this->buttonListener->onButtonReleased(button);
	}

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		//check if btn is within mouse coord
		sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
		sf::FloatRect bounds = button->getGlobalBounds();

		if (bounds.contains(mousePos))
		{
			this->pressed = true;
			button->changeButtonToPressed();
			this->buttonListener->onButtonClick(button);
		}
	}
}
