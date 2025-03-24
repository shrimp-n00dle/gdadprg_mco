#include "UIButton.hpp"

UIButton::UIButton(std::string name, sf::Texture* normalTexture, sf::Texture* pressedTexture) : AGameObject(name)
{
	this->normalTexture = normalTexture;
	this->pressedTexture = pressedTexture;
}

void UIButton::initialize()
{
	//std::cout << "button Declared as " << this->getName() << std::endl;
	sprite = new sf::Sprite();
	sprite->setTexture(*this->normalTexture);
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("Button");
	renderer->assignDrawable(sprite);
	attachComponent(renderer);
}

void UIButton::setButtonListener(ButtonListener* listener)
{
	//assign input controller
	this->listener = listener;
	UIButtonInput* inputController = new UIButtonInput("UI_InputController", this->listener);
	this->attachComponent(inputController);
}

void UIButton::changeButtonToNormal()
{
	this->sprite->setTexture(*this->normalTexture);
}

void UIButton::changeButtonToPressed() 
{
	this->sprite->setTexture(*this->pressedTexture);
}

sf::FloatRect UIButton::getLocalBounds()
{
	return this->sprite->getLocalBounds();
}

sf::FloatRect UIButton::getGlobalBounds()
{
	sf::FloatRect bounds = this->sprite->getGlobalBounds();

	AGameObject* parentObj = this;
	std::vector<AGameObject*> parentList;

	while (parentObj != nullptr)
	{
		parentList.push_back(parentObj);
		parentObj = parentObj->getParent();
	}

	sf::Transform transform = sf::Transform::Identity;
	int startIdx = parentList.size() - 1;
	for (int i = startIdx; i >= 0; i--)
	{
		transform = transform * parentList[i]->getTransformable()->getTransform();
	}

	bounds = transform.transformRect(bounds);

	/*
	* Insert calculation for global bounds here
	*/

	/*
	* std::cout << std::endl;
	* std::cout << this->name << std::endl;
	* std::cout << bounds.left << " : " << bounds.width << std::endl;
	* std::cout << bounds.top << " : " << bounds.height << std::endl;
	*/

	return bounds;
}

