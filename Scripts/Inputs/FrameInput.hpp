#pragma once
#include "GenericInput.hpp"

class FrameInput : public GenericInput
{
public:
	FrameInput(std::string name);
	~FrameInput();

	void perform();

	bool isLeft();
	bool isRight();

	void setLeft(bool flag);
	void setRight(bool flag);

private:
	bool keyFlag = false;
	bool goLeft = false;
	bool goRight = false;
	//const float SPEED_MULTIPLIER = 100.0f;
};

