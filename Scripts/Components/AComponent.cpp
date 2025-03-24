#include "AComponent.hpp"

AComponent::AComponent(std::string name, ComponentType type)
{
	this->name = name;
	this->owner = nullptr;
	this->type = type;
}

AComponent::~AComponent()
{
	this->owner = nullptr;
	this->type = NotSet;
}

AGameObject* AComponent::getOwner()
{
	return this->owner;
}

AComponent::ComponentType AComponent::getType()
{
	return this->type;
}

std::string AComponent::getName()
{
	return this->name;
}

void AComponent::setDeltaTime(sf::Time deltaTime)
{
	this->deltaTime = deltaTime;
}

void AComponent::attachOwner(AGameObject* object)
{
	this->owner = object;
}

void AComponent::detachOwner()
{
	/*if the obj owner gets detached, component must be deleted*/
	delete this;
}
