#pragma once
#include "GenericInput.hpp"

class BGInput : public GenericInput
{
public:
	BGInput(std::string name);
	~BGInput();

	void perform();

private:
	const float SPEED_MULTIPLIER = 100.0f;
};

