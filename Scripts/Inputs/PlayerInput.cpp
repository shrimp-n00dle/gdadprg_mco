#include "PlayerInput.hpp"

PlayerInput::PlayerInput(std::string name) : GenericInput(name) {}

PlayerInput::~PlayerInput()
{
	GenericInput::~GenericInput();
}

void PlayerInput::perform()
{

	//if (event.type == sf::Event::KeyPressed)
	//{
	//	keyFlag = true;
	//}
	//else if (event.type == sf::Event::KeyReleased)
	//{
	//	keyFlag = false;
	//}

	//switch (event.key.code)
	//{
	//case sf::Keyboard::W:
	//	moveUp = keyFlag;
	//	break;
	//case sf::Keyboard::A:
	//	moveLeft = keyFlag;
	//	break;
	//case sf::Keyboard::S:
	//	moveDown = keyFlag;
	//	break;
	//case sf::Keyboard::D:
	//	moveRight = keyFlag;
	//	break;
	//case sf::Keyboard::Space:
	//	this->fire = keyFlag;
	//	break;

	//}
}

//bool PlayerInput::isUp() { return moveUp; }
//bool PlayerInput::isDown() { return moveDown; }
//bool PlayerInput::isLeft() { return moveLeft; }
//bool PlayerInput::isRight() { return moveRight; }
//bool PlayerInput::hasFired() { return this->fire; }