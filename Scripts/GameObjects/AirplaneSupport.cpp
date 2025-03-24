#include "AirplaneSupport.hpp"

AirplaneSupport::AirplaneSupport(std::string name) : AGameObject(name) 
{
	this->name = name;
}

void AirplaneSupport::initialize()
{
	std::cout << "Declared as " << this->getName() << std::endl;
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTexture("raptor"));

	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
	this->sprite->setPosition(0, 0);

	/*Assign components*/
	AirplaneSupportMovement* logicComponent = new AirplaneSupportMovement("SupportMovement_1");
	this->attachComponent(logicComponent);

	Renderer* renderer = new Renderer("Support");
	renderer->assignDrawable(this->sprite);
	attachComponent(renderer);
}

void AirplaneSupport::processInput(sf::Event event) {}

