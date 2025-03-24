#include "EGameObject.hpp"
EGameObject::EGameObject(std::string name) : AGameObject(name)
{
	this->name = name;
}

void EGameObject::initialize() {}