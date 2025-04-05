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
	previousPosition = frameSprite->getPosition();
	if (!bGrounded) {  // Apply gravity only when not grounded
		velocity.y += 9.8f * deltaTime.asSeconds();
		frameSprite->move(0, velocity.y);
	}
	else {
		//when grounded
		velocity.y = 0.0f;
		//frameSprite->move(barrelDirection,velocity.y);

	}

	if (!platformsCollidingWith.empty()) {
		// Find the highest platform (platform with LOWEST Y value)
		float highestPlatformY = std::numeric_limits<float>::max();
		float playerHeight = frameSprite->getGlobalBounds().height;
		float highestPlatformHeight = 0;

		for (Collider* platform : platformsCollidingWith) {
			sf::FloatRect platformBounds = platform->getGlobalBounds();
			if (platformBounds.top < highestPlatformY) {
				highestPlatformY = platformBounds.top;
				highestPlatformHeight = platform->getGlobalBounds().height;
			}
		}
		frameSprite->setPosition(frameSprite->getPosition().x, highestPlatformY - (highestPlatformHeight * 2.0) - playerHeight);
	}

	AGameObject::update(deltaTime);
}
void Barrel::initialize()
{
	frameSprite = new sf::Sprite();
	frameSprite->setTexture(*TextureManager::getInstance()->getTexture("barrel_sheet"));
	sf::Vector2u textureSize = frameSprite->getTexture()->getSize();
	frameSprite->setScale(2.0f, 2.0f);

	setChildPosition(60, 220);

	Renderer* renderer = new Renderer("BarrelSprite");
	renderer->assignDrawable(frameSprite);
	attachComponent(renderer);

	this->collider = new Collider("BarrelCollider");
	this->collider->setLocalBounds(frameSprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(this->collider);

	//BarrelBehaviour* barrelBehaviour = new BarrelBehaviour("BarrelBehaviour");
	//this->attachComponent(barrelBehaviour);
}

void Barrel::onCollisionEnter(AGameObject* object)
{
	/*When it collides with the oilcan*/
	if (object->getName().find("player") != std::string::npos)
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
		std::cout << "Barrel: Collided with " << object->getName() << "\n";

		Collider* playerCollider = dynamic_cast<Collider*>(this->findComponentByType(AComponent::Physics, "BarrelCollider"));
		std::vector<AComponent*> platformColliders = object->getComponentsOfType(AComponent::Physics);
		bool hasLanded = false;

		for (AComponent* component : platformColliders) {
			Collider* platformCollider = dynamic_cast<Collider*>(component);
			if (platformCollider && platformCollider->hasCollisionWith(playerCollider)) {
				//std::cout << "Found colliding platform: " << platformCollider->getName() << std::endl;

				sf::FloatRect playerBounds = playerCollider->getGlobalBounds();
				sf::FloatRect platformBounds = platformCollider->getGlobalBounds();

				// Check if this is a collision from above (player's bottom vs platform's top)
				float playerBottom = playerBounds.top + playerBounds.height;
				bool collidingFromAbove = (playerBottom >= platformBounds.top - 4.0f &&
					previousPosition.y + playerBounds.height <= platformBounds.top + 4.0f);

				if (collidingFromAbove) {
					platformsCollidingWith.insert(platformCollider);

					if (!hasLanded && velocity.y > 0) {
						velocity.y = 0.f;
						bGrounded = true;
						hasLanded = true;
					}
				}
				else {
					// Handle collision from below or side
					// If from below, we may want to make the player bounce or just stop upward velocity
					if (velocity.y < 0) {
						velocity.y = 0;
					}
					frameSprite->setPosition(previousPosition);
				}
			}
		}
		return;
	}
}
void Barrel::onCollisionExit(AGameObject* object) {}

