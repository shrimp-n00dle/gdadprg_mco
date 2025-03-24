#include "GenericInput.hpp"

GenericInput::GenericInput(std::string name) : AComponent(name, Input)
{
	this->type = Input;
}

GenericInput::~GenericInput()
{
	AComponent::~AComponent();
}

void GenericInput::assignEvent(sf::Event event)
{
	this->event = event;
}

void GenericInput::perform() {}

