#include "Hammer.hpp"

Hammer::Hammer(std::string name) : APoolable(name), CollisionListener() {};

Hammer::~Hammer()
{
	delete this->sprite;
}

void Hammer::onRelease()
{
	PhysicsManager::getInstance()->untrackObject(this->collider);
}

void Hammer::onActivate()
{
	PhysicsManager::getInstance()->trackObject(this->collider);
}

APoolable* Hammer::clone()
{
	APoolable* copyObj = new Hammer(name);
	return copyObj;
}

void Hammer::initialize()
{
	sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("hammer"));
	sprite->setScale(2.0f, 2.0f);
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	setChildPosition(60, 300);

	Renderer* renderer = new Renderer("HammerSprite");
	renderer->assignDrawable(sprite);
	attachComponent(renderer);

	this->collider = new Collider("HammerCollider");
	this->collider->setLocalBounds(sprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(this->collider);
}

void Hammer::onCollisionEnter(AGameObject* object)
{
	if (object->getName().find("player") != std::string::npos)
	{
		std::cout << "Hammer: collided with " << object->getName() << std::endl;

		/*Delete hammer clone*/
		GameObjectPool* hammerPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::HAMMER_POOL_TAG);
		hammerPool->releasePoolable((APoolable*)this);
		return;
	}
}
void Hammer::onCollisionExit(AGameObject* object) {}

