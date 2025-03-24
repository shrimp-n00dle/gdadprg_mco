#include "ProjectileObject.hpp"

ProjectileObject::ProjectileObject(std::string name) : APoolable(name), CollisionListener() {}

void ProjectileObject::initialize()
{
	this->sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("bullet"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("EnemySprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	this->projectileMovement = new ProjectileMovement("projectile_movement");
	this->attachComponent(this->projectileMovement);

	this->collider = new Collider("EnemyCollider");

	collider->setLocalBounds(sprite->getGlobalBounds());
	collider->setCollisionListener(this);
	this->attachComponent(collider);
}

void ProjectileObject::onRelease()
{
	PhysicsManager::getInstance()->untrackObject(this->collider);
}

void ProjectileObject::onActivate()
{
	//reset state
	AirplanePlayer* player = (AirplanePlayer*)GameObjectManager::getInstance()->findObjectByName("PlaneObject");
	sf::Vector2f position = player->getTransformable()->getPosition();
	this->setChildPosition(position.x, position.y);

	this->hasHit = false;

	PhysicsManager::getInstance()->trackObject(this->collider);
}

APoolable* ProjectileObject::clone()
{
	APoolable* copyObj = new ProjectileObject(this->name);
	return copyObj;
}

void ProjectileObject::onCollisionEnter(AGameObject* object)
{
	if (object->getName().find("enemy") != std::string::npos && !this->hasHit)
	{
		std::cout << "PROJECTILE OBJ: Collided with " << object->getName() << "\n";
		return;
		this->hasHit = true;
		GameObjectPool* projectilePool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::PROJECTILE_POOL_TAG);
		projectilePool->releasePoolable((APoolable*)this);
		std::cout << "HIT" << std::endl;
	}
}
void ProjectileObject::onCollisionExit(AGameObject* object)
{
	//std::cout << "Collsion exit with " << object->getName() << std::endl;
}