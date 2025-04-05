#include "OilCan.hpp"

OilCan::OilCan(std::string name) : APoolable(name), CollisionListener() {};

OilCan::~OilCan()
{
	delete this->frameSprite;
}

void OilCan::onRelease() {}

void OilCan::onActivate() {}

APoolable* OilCan::clone()
{
	APoolable* copyObj = new OilCan(name);
	return copyObj;
}

void OilCan::initialize()
{
	frameSprite = new sf::Sprite();
	frameSprite->setTexture(*TextureManager::getInstance()->getTexture("can_sheet"));
	sf::Vector2u textureSize = frameSprite->getTexture()->getSize();
	frameSprite->setScale(2.5f, 2.5f);

	//setChildPosition(600,250);
	setChildPosition(100, 710);

	Renderer* renderer = new Renderer("OilCanSprite");
	renderer->assignDrawable(frameSprite);
	attachComponent(renderer);

	CBehaviour* cBehaviour = new CBehaviour("CBehaviour");
	this->attachComponent(cBehaviour);
}

void OilCan::update(sf::Time deltaTime)
{
	timer -= deltaTime.asSeconds();
	AGameObject::update(deltaTime);
}

void OilCan::onCollisionEnter(AGameObject* object) {}
void OilCan::onCollisionExit(AGameObject* object) {}

