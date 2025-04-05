#include "Barrel.hpp"

Barrel::Barrel(std::string name) : APoolable(name), CollisionListener() {};

Barrel::~Barrel()
{
	delete this->frameSprite;
}

void Barrel::onRelease()
{
	PhysicsManager::getInstance()->untrackObject(this->collider);
}

void Barrel::onActivate()
{
	PhysicsManager::getInstance()->trackObject(this->collider);
}

APoolable* Barrel::clone()
{
	APoolable* copyObj = new Barrel(name);
	return copyObj;
}

void Barrel::update(sf::Time deltaTime) 
{
	if (isGrounded())
	{
		if (bLeft)this->getTransformable()->move(1, 0);
		else this->getTransformable()->move(-1, 0);
	}
	else if (!isGrounded())
	{
		this->getTransformable()->move(0, 9.8f);
	}
	/*Animation purposes*/
	timer -= deltaTime.asSeconds();


	AGameObject::update(deltaTime);
}

void Barrel::initialize()
{
	frameSprite = new sf::Sprite();
	frameSprite->setTexture(*TextureManager::getInstance()->getTexture("barrel_sheet"));
	sf::Vector2u textureSize = frameSprite->getTexture()->getSize();
	frameSprite->setScale(2.0f, 2.0f);

	setChildPosition(200, 240);

	Renderer* renderer = new Renderer("BarrelSprite");
	renderer->assignDrawable(frameSprite);
	attachComponent(renderer);

	this->collider = new Collider("BarrelCollider");
	this->collider->setLocalBounds(frameSprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(this->collider);

	BarrelBehaviour* barrelBehaviour = new BarrelBehaviour("BarrelBehaviour");
	this->attachComponent(barrelBehaviour);
}

void Barrel::onCollisionEnter(AGameObject* object)
{
	/*When it collides with the oilcan*/
	if (object->getName().find("oilcan") != std::string::npos)
	{
		std::cout << "Barrel: collided with " << object->getName() << std::endl;
	
		/*Delete Barrel clone*/
		GameObjectPool* BarrelPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::BARREL_POOL_TAG);
		BarrelPool->releasePoolable((APoolable*)this);
		return;
	}

	/*Collision on the platform*/
	if (object->getName().find("level1Map") != std::string::npos)
	{
		onGround = true;
	}

	/*Collision on the platform*/
	if (object->getName().find("Checker1") != std::string::npos)
	{
		std::cout << "Barrel collided with checker!!!!!" << std::endl;
		onGround = false;
		if (bLeft) bLeft = false;
		else if (!bLeft) bLeft = true;
	}

	/*Collision on the platform*/
	if (object->getName().find("Checker2") != std::string::npos)
	{
		std::cout << "CHECKER2" << std::endl;
		onGround = false;
	}

}
void Barrel::onCollisionExit(AGameObject* object) 
{
	/*if (object->getName().find("level1Map") != std::string::npos)
	{
		onGround = false;
		if (bLeft) bLeft = false;
		else if (!bLeft) bLeft = true;
	}*/
}

