#include "Kong.hpp"

Kong::Kong(std::string name) : APoolable(name), CollisionListener() {};

Kong::~Kong()
{
	delete this->frameSprite;
}

void Kong::onRelease() {}

void Kong::onActivate() {}

APoolable* Kong::clone()
{
	APoolable* copyObj = new Kong(name);
	return copyObj;
}

void Kong::initialize()
{
	/*Sprite initialization*/
	frameSprite = new sf::Sprite();
	frameSprite->setTexture(*TextureManager::getInstance()->getTexture("kong_sheet"));
	sf::Vector2u textureSize = frameSprite->getTexture()->getSize();
	frameSprite->setScale(2.8f, 2.8f);

	setChildPosition(120, 205);

	Renderer* renderer = new Renderer("KongSprite");
	renderer->assignDrawable(frameSprite);
	attachComponent(renderer);

	KBehaviour* kBehaviour = new KBehaviour("KBehaviour");
	this->attachComponent(kBehaviour);
}

void Kong::update(sf::Time deltaTime)
{
	//Timer for how long the next frame will be called
	timer -= deltaTime.asSeconds();
	AGameObject::update(deltaTime);
}

void Kong::onCollisionEnter(AGameObject* object) {}
void Kong::onCollisionExit(AGameObject* object) {}

