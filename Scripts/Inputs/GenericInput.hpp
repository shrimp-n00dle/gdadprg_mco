#pragma once
#include "../Components/AComponent.hpp"
class GenericInput : public AComponent
{
public:
	GenericInput(std::string name);
	~GenericInput();

	void perform();
	void assignEvent(sf::Event event);

protected:
	sf::Event event;
};

