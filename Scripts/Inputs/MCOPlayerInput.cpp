#include "MCOPlayerInput.hpp"

MCOPlayerInput::MCOPlayerInput(std::string name) : GenericInput(name) {}

MCOPlayerInput::~MCOPlayerInput()
{
	GenericInput::~GenericInput();
}

void MCOPlayerInput::perform()
{

	if (event.type == sf::Event::KeyPressed)
	{
		keyFlag = true;
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		keyFlag = false;
	}

	switch (event.key.code)
	{
	case sf::Keyboard::W:
		moveUp = keyFlag;
		break;
	case sf::Keyboard::A:
		moveLeft = keyFlag;
		break;
	case sf::Keyboard::S:
		moveDown = keyFlag;
		break;
	case sf::Keyboard::D:
		moveRight = keyFlag;
		break;
	case sf::Keyboard::Space:
		bJump = keyFlag;
	}
}

bool MCOPlayerInput::isUp() { return moveUp; }
bool MCOPlayerInput::isDown() { return moveDown; }
bool MCOPlayerInput::isLeft() { return moveLeft; }
bool MCOPlayerInput::isRight() { return moveRight; }
bool MCOPlayerInput::isJump() { return bJump; }


void MCOPlayerInput::setLeft(bool flag) { moveLeft = flag; }

void MCOPlayerInput::setRight(bool flag) { moveRight = flag; }