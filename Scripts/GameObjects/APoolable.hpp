#pragma once
#include "AGameObject.hpp"

class APoolable : public AGameObject
{
public:
	APoolable(std::string name);

	//initialize property of this object
	virtual void initialize() = 0;

	//throws this event when this obj has been released back to the pool
	virtual void onRelease() = 0;

	//throws the eventwhen the objhas been activiated from the pool
	virtual void onActivate() = 0;

	//provides a copy of the poolable instance, must be implemented per specific class
	virtual APoolable* clone() = 0;
};

