#include "Checker.hpp"

Checker::Checker(std::string name) : APoolable(name), CollisionListener() {};

Checker::~Checker()
{
	delete this->sprite;
}

void Checker::onRelease()
{
	PhysicsManager::getInstance()->untrackObject(this->collider);
}

void Checker::onActivate()
{
	PhysicsManager::getInstance()->trackObject(this->collider);
}

APoolable* Checker::clone()
{
	APoolable* copyObj = new Checker(name);
	return copyObj;
}

void Checker::initialize()
{
	/*Sprite initialization*/
	checkerSprite = new sf::RectangleShape();
	checkerSprite->setPosition(0, 0);
	checkerSprite->setOrigin(0, 0);
	checkerSprite->setSize(sf::Vector2f(70, 35));
	//checkerSprite->setFillColor(sf::Color(0, 255, 0, 100));  // Semi-transparent Blue
	//checkerSprite->setOutlineColor(sf::Color::Blue);
	//checkerSprite->setOutlineThickness(2);

	//Renderer* renderer = new Renderer("CheckerSprite");
	//renderer->assignDrawable(checkerSprite);
	//attachComponent(renderer);

	this->collider = new Collider("CheckerCollider");
	this->collider->setLocalBounds(checkerSprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(this->collider);
	PhysicsManager::getInstance()->trackObject(this->collider);
}

void Checker::onCollisionEnter(AGameObject* object) {}
void Checker::onCollisionExit(AGameObject* object) {}

