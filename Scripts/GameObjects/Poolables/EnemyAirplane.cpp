#include "EnemyAirplane.hpp"

EnemyAirplane::EnemyAirplane(std::string name) : APoolable(name), CollisionListener()
{
}; 

EnemyAirplane::~EnemyAirplane()
{
	delete this->sprite;
}


void EnemyAirplane::onRelease()
{
	PhysicsManager::getInstance()->untrackObject(this->collider);
}

void EnemyAirplane::onActivate()
{
	//EnemyBehaviour* behaviour = (EnemyBehaviour*)findComponentByName("EnemyBehaviour");
	//behaviour->reset();

	PhysicsManager::getInstance()->trackObject(this->collider);

	setChildPosition(Game::WINDOW_WIDTH / 2, 0);
	getTransformable()->move(rand() % SPAWN_RANGE - rand() % SPAWN_RANGE, 50);
}

APoolable* EnemyAirplane::clone()
{
	APoolable* copyObj = new EnemyAirplane(name);
	return copyObj;
}

void EnemyAirplane::initialize()
{
	sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("avenger"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	setChildPosition(640 / 2, -30);
	getTransformable()->move(rand() % SPAWN_RANGE - rand() % SPAWN_RANGE, 0);
	getTransformable()->setRotation(180);

	Renderer* renderer = new Renderer("EnemySprite");
	renderer->assignDrawable(sprite);
	attachComponent(renderer);

	/*EnemyBehaviour* behaviour = new EnemyBehaviour("EnemyBehaviour");
	attachComponent(behaviour);
	behaviour->configure(1.0f);*/

	this->collider = new Collider("EnemyCollider");
	this->collider->setLocalBounds(sprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(this->collider);
}

void EnemyAirplane::onCollisionEnter(AGameObject* object)
{
	//if (object->getName().find("projectile") != std::string::npos)
	if (object->getName().find("PlaneObject") != std::string::npos)
	{
		std::cout << "ENEMYAIRPLANE: EnemyPlane collided with " << object->getName() << std::endl;
		return;
		GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG);
		enemyPool->releasePoolable((APoolable*)this);
	}
}
void EnemyAirplane::onCollisionExit(AGameObject* object) 
{
	//std::cout << "EnemyPlane collision exit with " << object->getName() << std::endl;
}

