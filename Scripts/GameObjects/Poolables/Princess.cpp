#include "Princess.hpp"

Princess::Princess(std::string name) : APoolable(name), CollisionListener() {};

Princess::~Princess()
{
	delete this->frameSprite;
}

void Princess::onRelease() {}

void Princess::onActivate() {}

APoolable* Princess::clone()
{
	APoolable* copyObj = new Princess(name);
	return copyObj;
}

void Princess::initialize()
{
	frameSprite = new sf::Sprite();
	frameSprite->setTexture(*TextureManager::getInstance()->getTexture("princess_sheet"));
	sf::Vector2u textureSize = frameSprite->getTexture()->getSize();
	frameSprite->setScale(2.0f, 2.0f);

	setChildPosition(290,145);

	Renderer* renderer = new Renderer("PrincessSprite");
	renderer->assignDrawable(frameSprite);
	attachComponent(renderer);

	PBehaviour* pBehaviour = new PBehaviour("PBehaviour");
	this->attachComponent(pBehaviour);
}

void Princess::update(sf::Time deltaTime)
{
	timer -= deltaTime.asSeconds();
	std::cout << timer << " ";

	AGameObject::update(deltaTime);

}

void Princess::onCollisionEnter(AGameObject* object) {}
void Princess::onCollisionExit(AGameObject* object) {}

