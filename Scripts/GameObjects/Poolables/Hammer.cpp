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

	//Game::WINDOW_WIDTH 
	setChildPosition(640/ 2, 0);
	getTransformable()->move(rand() % SPAWN_RANGE - rand() % SPAWN_RANGE, 50);
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
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setScale(0.1f, 0.1f);
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	setChildPosition(10, -30);
	getTransformable()->move(rand() % SPAWN_RANGE - rand() % SPAWN_RANGE, 0);

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

