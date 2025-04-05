#include "Player.hpp"

Player::Player(std::string name) : AGameObject(name), CollisionListener()
{
	this->name = name;
	this->sheetName = "walk_sheet";

}

void Player::initialize()
{
	frameSprite = new sf::Sprite();
	frameSprite->setTexture(*TextureManager::getInstance()->getTexture("walk_sheet"));
	sf::Vector2u textureSize = frameSprite->getTexture()->getSize();
	frameSprite->setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
	//this->transformable.setPosition(400.0f,80.0f);
	
	setChildPosition(150.0f, 60.0f);
	/*Add colliders*/
	this->collider = new Collider("PlayerCollider");
	this->collider->setLocalBounds(frameSprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(this->collider);
	PhysicsManager::getInstance()->trackObject(this->collider);

	frameSprite->setScale(2.0f, 2.0f);
	frameSprite->setPosition(0.0f, 660.0f);

	Renderer* renderer = new Renderer("MCOPlayerSprite");
	renderer->assignDrawable(frameSprite);
	attachComponent(renderer);


	MCOPlayerInput* inputController = new MCOPlayerInput("MCOPlayerInput");
	this->attachComponent(inputController);

	MCOPlayerMovement* movement = new MCOPlayerMovement("MCOMovement");
	this->attachComponent(movement);

	WalkBehaviour* walkBehaviour = new WalkBehaviour("WalkBehaviour");
	this->attachComponent(walkBehaviour);

	LadderBehaviour* ladderBehaviour = new LadderBehaviour("LadderBehaviour");
	this->attachComponent(ladderBehaviour);

	HammerBehaviour* hammerBehaviour = new HammerBehaviour("HammerBehaviour");
	this->attachComponent(hammerBehaviour);

	/* Debug Lines for the bounding boxes */
	sf::RectangleShape* boundingBox = new sf::RectangleShape();
	boundingBox->setPosition(this->collider->getLocalBounds().left, this->collider->getLocalBounds().top);
	boundingBox->setOrigin(0, 0);
	boundingBox->setSize(sf::Vector2f(this->collider->getLocalBounds().width, this->collider->getLocalBounds().height));
	boundingBox->setFillColor(sf::Color(0, 0, 255, 100));  // Semi-transparent blue
	boundingBox->setOutlineColor(sf::Color::Red);
	boundingBox->setOutlineThickness(2);

	Renderer* boundingRenderer = new Renderer("PlayerCollisionBounds");
	boundingRenderer->assignDrawable(boundingBox);
	this->attachComponent(boundingRenderer);

	
}

void Player::processInput(sf::Event event) 
{
	AGameObject::processInput(event);
}

void Player::update(sf::Time deltaTime) {
	// Update previous position with last frame's final position
	previousPosition = frameSprite->getPosition();

	// Debug output for platforms every 2 seconds
	debugTimer += deltaTime;
	if (debugTimer >= sf::seconds(2.0f)) {
		std::cout << "\n=== Current Platforms Colliding With ===" << std::endl;
		if (platformsCollidingWith.empty()) {
			std::cout << "No platforms currently colliding" << std::endl;
		} else {
			for (Collider* platform : platformsCollidingWith) {
				std::cout << "Platform: " << platform->getName() << std::endl;
			}
		}
		std::cout << "====================================\n" << std::endl;
		debugTimer = sf::Time::Zero;
	}

	if (!bLadder && !bGrounded) {  // Apply gravity only when not grounded
		velocity.y += 9.8f * deltaTime.asSeconds();

		if (velocity.y > 500.0f) velocity.y = 500.0f;

		frameSprite->move(0, velocity.y);
	}
	else if (!bLadder) {
		velocity.y = 0.0f;
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

		float mainOffset = highestPlatformY - (highestPlatformHeight * 2.0f) - playerHeight;
		std::cout << "mainOffset = " << mainOffset << std::endl;
		if (frameSprite->getPosition().y - mainOffset > 1.0f)
			mainOffset = frameSprite->getPosition().y - 1.0f;
		else
			mainOffset = frameSprite->getPosition().y;
		frameSprite->setPosition(frameSprite->getPosition().x, mainOffset);
	}
	
	AGameObject::update(deltaTime);
}

void Player::onCollisionEnter(AGameObject* object)
{
	/*Eliminate player*/
	if (object->getName().find("barrel") != std::string::npos)
	{
		std::cout << "Player: Collided with " << object->getName() << "\n";
		//changeSpriteState("hit_sheet");
		return;
	}

	/*If the player has a hammer, delete the barrel*/
	if (object->getName().find("barrel") != std::string::npos && bHammer)
	{
		std::cout << "Player: Collided with " << object->getName() << "\n";
		return;
	}
	
	/*Attacked by fireballs and no hammer*/
	if (object->getName().find("enemy") != std::string::npos && !bHammer)
	{
		std::cout << "Player: Collided with " << object->getName() << "\n";
		//changeSpriteState("hit_sheet");
		return;
	}

	/*Attacked by fireballs with hammer*/
	if (object->getName().find("enemy") != std::string::npos && bHammer)
	{
		std::cout << "Player: Collided with " << object->getName() << "\n";
		return;
	}

	/*Ladder collision with player*/
	if (object->getName().find("ladder") != std::string::npos && !bHammer)
	{
		std::cout << "Player: Collided with " << object->getName() << "\n";
		/*Ladder Behaviour initialized the sprite*/
		if (!bLadder)
		{
			changeSpriteState("climb_sheet");
		}
		bLadder = true;
		return;
	}

	/*Hammer collision with player*/
	if (object->getName().find("hammer") != std::string::npos)
	{
		std::cout << "Player: Collided with " << object->getName() << "\n";

		/*Switch the frame to hammer mode*/
		changeSpriteState("hammer_sheet");
		return;
	}

	/*Platform collision with player*/
	if (object->getName().find("level1Map") != std::string::npos)
	{
		std::cout << "Player: Collided with " << object->getName() << "\n";

		Collider* playerCollider = dynamic_cast<Collider*>(this->findComponentByType(AComponent::Physics, "PlayerCollider"));
		std::vector<AComponent*> platformColliders = object->getComponentsOfType(AComponent::Physics);
		bool hasLanded = false;

		for (AComponent* component : platformColliders) {
			Collider* platformCollider = dynamic_cast<Collider*>(component);
			if (platformCollider && platformCollider->hasCollisionWith(playerCollider)) {
				std::cout << "Found colliding platform: " << platformCollider->getName() << std::endl;

				sf::FloatRect playerBounds = playerCollider->getGlobalBounds();
				sf::FloatRect platformBounds = platformCollider->getGlobalBounds();

				float playerBottom = playerBounds.top + playerBounds.height;
				float previousPlayerBottom = previousPosition.y + (playerBounds.height / 2.0f);
				bool collidingFromAbove = (playerBottom >= platformBounds.top - 4.0f);
					//&& previousPlayerBottom <= platformBounds.top + 4.0f);

				std::cout << "PlayerBottom: " << playerBottom << " = " << playerBounds.top << " + " << playerBounds.height << std::endl;
				std::cout << "PreviousPlayerBottom: " << previousPlayerBottom << " = " 
					<< previousPosition.y << " + (" << playerBounds.height << " / 2.0 )\n";
				std::cout << "PlayerBottom Collision?: " << playerBottom << " >= " <<
					platformBounds.top << " - 4.0 " << std::endl;
				std::cout << "Collision #2?: " << previousPlayerBottom << " <= " <<
					platformBounds.top << " + 4.0 " << std::endl;

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
					std::cout << "Not really colliding from above tho" << std::endl;
					
					bool movingUpward = velocity.y < 0;  // Using velocity instead of position comparison
					std::cout << "movingUpward = velocity.y(" << velocity.y << ") < 0" << std::endl;
					if (movingUpward && playerBottom >= platformBounds.top - 4.0f) {
						// We're moving up and have reached/passed the platform top - treat it like landing
						std::cout << "still going to insert it anyways" << std::endl;
						platformsCollidingWith.insert(platformCollider);
						velocity.y = 0.f;
						bGrounded = true;
						hasLanded = true;
					} 
					else if (velocity.y < 0) {
						// We're moving up but hit the bottom of a platform
						velocity.y = 0;
						frameSprite->setPosition(previousPosition);
					} 
					else {
						// Side collision
						frameSprite->setPosition(previousPosition);
					}
				}
			}
		}
		return;
	}
}

void Player::onCollisionExit(AGameObject* object)
{
	if (object->getName().find("ladder") != std::string::npos) {
		bLadder = false;
		bGrounded = true;
		changeSpriteState("walk_sheet");
	}

	if (object->getName().find("level1Map") != std::string::npos)
	{
		Collider* playerCollider = dynamic_cast<Collider*>(this->findComponentByType(AComponent::Physics, "PlayerCollider"));
		if (!playerCollider) return;

		std::vector<AComponent*> platformColliders = object->getComponentsOfType(AComponent::Physics);
		std::set<Collider*> platformsToRemove;

		for (Collider* platform : platformsCollidingWith) {
			if (platform->getOwner() == object && !platform->hasCollisionWith(playerCollider)) {
				platformsToRemove.insert(platform);
			}
		}

		for (Collider* platform : platformsToRemove) {
			platformsCollidingWith.erase(platform);
			std::cout << "No longer colliding with platform: " << platform->getName() << std::endl;
			if (platformsCollidingWith.empty()) {
				bGrounded = false;
				std::cout << "Player is no longer grounded" << std::endl;
			}
		}
	}
}

void Player::changeSpriteState(std::string textureName)
{
	sheetName = textureName;
	/*Change to hammer_sheet after testing*/
	if (textureName == "hammer_sheet")
	{
		/*Player will not change sprite while hammer mode is still engaged*/
		bHammer = true;
	}

	/*Reassign the sprite*/
	frameSprite->setTexture(*TextureManager::getInstance()->getTexture(textureName));
	sf::Vector2u textureSize = frameSprite->getTexture()->getSize();
	frameSprite->setScale(2.0f, 2.0f);

	Renderer* renderer = new Renderer("MCOPlayerSprite");
	renderer->assignDrawable(frameSprite);
	attachComponent(renderer);

	/*Reassign collider*/
	this->collider->setLocalBounds(frameSprite->getGlobalBounds());
}

Collider* Player::getCollider()
{
	return this->collider;
}

std::string Player::getSheetName()
{
	return sheetName;
}

