#pragma once
#include "GenericInput.hpp"
#include "../GameObjects/UI/UIButton.hpp"
#include "../GameObjects/Listeners/ButtonListener.hpp"
#include "iostream"
#include "string"
class UIButtonInput : public GenericInput
{
public:
	UIButtonInput(std::string name, ButtonListener* buttonListener);
	~UIButtonInput();

	void perform();

private:
	ButtonListener* buttonListener;
	bool pressed = false;
};

