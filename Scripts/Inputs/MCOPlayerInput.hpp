#pragma once
#include "GenericInput.hpp"
#include "../GameObjects/Player.hpp"
class MCOPlayerInput : public GenericInput
{
public:
	MCOPlayerInput(std::string name);
	~MCOPlayerInput();

	void perform();
	bool isUp();
	bool isDown();
	bool isLeft();
	bool isRight();
	bool isJump();

	void setLeft(bool flag);
	void setRight(bool flag);

private:
	const float SPEED_MULTIPLIER = 300.0f;
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
	bool keyFlag = false;
	bool bJump = false;
};

