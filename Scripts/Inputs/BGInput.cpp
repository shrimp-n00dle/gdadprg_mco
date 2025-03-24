#include "BGInput.hpp"

BGInput::BGInput(std::string name) : GenericInput(name) {}

BGInput::~BGInput()
{
	GenericInput::~GenericInput();
}

void BGInput::perform()
{
}
