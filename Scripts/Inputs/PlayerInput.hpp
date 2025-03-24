#pragma once
#include "GenericInput.hpp"
class PlayerInput : public GenericInput
{
public:
	PlayerInput(std::string name);
	~PlayerInput();

	void perform();
	//bool isUp();
	//bool isDown();
	//bool isLeft();
	//bool isRight();
	//bool hasFired();

private:
	const float SPEED_MULTIPLIER = 300.0f;
	//bool moveUp = false;
	//bool moveDown = false;
	//bool moveLeft = false;
	//bool moveRight = false;
	//bool keyFlag = false;
	//bool fire = false;
};

