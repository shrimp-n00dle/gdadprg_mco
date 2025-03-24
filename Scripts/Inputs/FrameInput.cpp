#include "FrameInput.hpp"

FrameInput::FrameInput(std::string name) : GenericInput(name) {}

FrameInput::~FrameInput()
{
	GenericInput::~GenericInput();
}

void FrameInput::perform()
{

	if (event.type == sf::Event::KeyPressed) keyFlag = true;
	else if (event.type == sf::Event::KeyReleased) keyFlag = false;

	switch (event.key.code)
	{
		case sf::Keyboard::A:
			goLeft = keyFlag;
			break;
		case sf::Keyboard::D:
			goRight = keyFlag;
			break;
	}
}

bool FrameInput::isLeft() { return goLeft; }
bool FrameInput::isRight() { return goRight; }

void FrameInput::setLeft(bool flag) { goLeft = flag; }

void FrameInput::setRight(bool flag) { goRight = flag; }

