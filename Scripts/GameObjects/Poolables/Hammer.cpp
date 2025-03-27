#include "Hammer.hpp"

Hammer::Hammer(std::string name) : APoolable(name), CollisionListener()
{
};

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
	//EnemyBehaviour* behaviour = (EnemyBehaviour*)findComponentByName("EnemyBehaviour");
	//behaviour->reset();

	PhysicsManager::getInstance()->trackObject(this->collider);

	setChildPosition(Game::WINDOW_WIDTH / 2, 0);
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
	sprite->setScale(0.5f, 0.5f);
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	setChildPosition(640 / 2, -30);
	getTransformable()->move(rand() % SPAWN_RANGE - rand() % SPAWN_RANGE, 0);

	Renderer* renderer = new Renderer("HammerSprite");
	renderer->assignDrawable(sprite);
	attachComponent(renderer);

	/*EnemyBehaviour* behaviour = new EnemyBehaviour("EnemyBehaviour");
	attachComponent(behaviour);
	behaviour->configure(1.0f);*/

	this->collider = new Collider("HammerCollider");
	this->collider->setLocalBounds(sprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(this->collider);
}

void Hammer::onCollisionEnter(AGameObject* object)
{
	//std::cout << "Hammer collision" << std::endl;
	if (object->getName().find("player") != std::string::npos)
	{
		std::cout << "Hammer: collided with " << object->getName() << std::endl;
		return;
		//GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG);
		//enemyPool->releasePoolable((APoolable*)this);
	}
}
void Hammer::onCollisionExit(AGameObject* object)
{
	//std::cout << "EnemyPlane collision exit with " << object->getName() << std::endl;
}

