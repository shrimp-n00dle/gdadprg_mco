#include "OilCan.hpp"

OilCan::OilCan(std::string name) : APoolable(name), CollisionListener() {};

OilCan::~OilCan()
{
	delete this->frameSprite;
}

void OilCan::onRelease() { PhysicsManager::getInstance()->untrackObject(this->collider); }

void OilCan::onActivate() { PhysicsManager::getInstance()->trackObject(this->collider); }

APoolable* OilCan::clone()
{
	APoolable* copyObj = new OilCan(name);
	return copyObj;
}

void OilCan::initialize()
{
	/*Sprite initialization*/
	frameSprite = new sf::Sprite();
	frameSprite->setTexture(*TextureManager::getInstance()->getTexture("can_sheet"));
	sf::Vector2u textureSize = frameSprite->getTexture()->getSize();
	frameSprite->setScale(2.5f, 2.5f);

	setChildPosition(100, 710);

	Renderer* renderer = new Renderer("OilCanSprite");
	renderer->assignDrawable(frameSprite);
	attachComponent(renderer);

	CBehaviour* cBehaviour = new CBehaviour("CBehaviour");
	this->attachComponent(cBehaviour);

	this->collider = new Collider("OilCanCollider");
	this->collider->setLocalBounds(frameSprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(this->collider);
}

void OilCan::update(sf::Time deltaTime)
{
	//Timer for how long the next frame will be called
	timer -= deltaTime.asSeconds();
	AGameObject::update(deltaTime);
}

void OilCan::onCollisionEnter(AGameObject* object) {}
void OilCan::onCollisionExit(AGameObject* object) {}

