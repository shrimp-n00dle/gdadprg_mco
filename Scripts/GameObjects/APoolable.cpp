#include "APoolable.hpp"

APoolable::APoolable(std::string name) : AGameObject(name) {}

//initialize property of this object
void APoolable::initialize() {}

//throws this event when this obj has been released back to the pool
void APoolable::onRelease() {}

//throws the eventwhen the objhas been activiated from the pool
void APoolable::onActivate() {}

//provides a copy of the poolable instance, must be implemented per specific class
APoolable* APoolable::clone() { return nullptr; }