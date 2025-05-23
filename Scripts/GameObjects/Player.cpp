#include "Player.hpp"

Player::Player(std::string name) : AGameObject(name), CollisionListener()
{
	this->name = name;
	this->sheetName = "walk_sheet";

}

void Player::initialize()
{

	/*sprite initialization*/
	frameSprite = new sf::Sprite();
	frameSprite->setTexture(*TextureManager::getInstance()->getTexture("walk_sheet"));
	sf::Vector2u textureSize = frameSprite->getTexture()->getSize();
	frameSprite->setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
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

	/*Behaviour Components Added*/

	//For checking players input on the keyboard
	MCOPlayerInput* inputController = new MCOPlayerInput("MCOPlayerInput");
	this->attachComponent(inputController);

	//The feedback from the keyboards pressed
	MCOPlayerMovement* movement = new MCOPlayerMovement("MCOMovement");
	this->attachComponent(movement);

	//Focuses on the frame by frame animation of player walk
	WalkBehaviour* walkBehaviour = new WalkBehaviour("WalkBehaviour");
	this->attachComponent(walkBehaviour);

	//Focuses on the frame by frame animation of player climb
	LadderBehaviour* ladderBehaviour = new LadderBehaviour("LadderBehaviour");
	this->attachComponent(ladderBehaviour);

	//Focuses on the frame by frame animation of player hammer 
	HammerBehaviour* hammerBehaviour = new HammerBehaviour("HammerBehaviour");
	this->attachComponent(hammerBehaviour);

	//Focuses on the frame by frame animation when the player is hit
	HitBehaviour* hitBehaviour = new HitBehaviour("HitBehaviour");
	this->attachComponent(hitBehaviour);	
}

void Player::processInput(sf::Event event) 
{
	AGameObject::processInput(event);
}

void Player::update(sf::Time deltaTime) {
	
	//The hitTimer and hammerTimer holds how fast the frames pass for the Hit and Hammer mode of the player
	hitTimer -= deltaTime.asSeconds();
	hammerTimer -= deltaTime.asSeconds();

	previousPosition = frameSprite->getPosition();

	// Debug output for platforms every 2 seconds
	debugTimer += deltaTime;
	//if (debugTimer >= sf::seconds(2.0f)) {
	//	std::cout << "\n=== Current Platforms Colliding With ===" << std::endl;
	//	if (platformsCollidingWith.empty()) {
	//		std::cout << "No platforms currently colliding" << std::endl;
	//	} else {
	//		for (Collider* platform : platformsCollidingWith) {
	//			std::cout << "Platform: " << platform->getName() << std::endl;
	//		}
	//	}
	//	std::cout << "====================================\n" << std::endl;
	//	debugTimer = sf::Time::Zero;
	//}

	passiveScoreTimer += deltaTime.asSeconds();
	if (passiveScoreTimer >= PASSIVE_SCORE_INTERVAL) {
		ScoreManager::getInstance()->addScore(PASSIVE_SCORE_AMOUNT);
		passiveScoreTimer = 0.0f;
		std::cout << "Added " << PASSIVE_SCORE_AMOUNT << " passive points! Total: "
			<< ScoreManager::getInstance()->getScore() << std::endl;
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

		mainOffset = highestPlatformY - (highestPlatformHeight * 2.0f) - playerHeight;
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
	if (object->getName().find("Goal") != std::string::npos) 
	{
		ResultScreen* resultScreen = (ResultScreen*)GameObjectManager::getInstance()->findObjectByName("ResultScreen");
		resultScreen->setEnabled(true);
		SFXManager::getInstance()->setBGMLoop(false);
		SFXManager::getInstance()->stopBGM();
		SFXManager::getInstance()->playSound(AudioKeys::VICTORY);
		ApplicationManager::getInstance()->pauseApplication();
		return;
	}

	/*Eliminate player*/
	if (object->getName().find("barrel") != std::string::npos)
	{
		changeSpriteState("hit_sheet");
		return;
	}

	/*If the player has a hammer, delete the barrel*/
	if (object->getName().find("barrel") != std::string::npos && bHammer)
	{
		/*Delete hammer clone*/
		GameObjectPool* barrelPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::BARREL_POOL_TAG);
		barrelPool->releasePoolable((APoolable*)this);
		return;
	}

	/*Ladder collision with player*/
	if (object->getName().find("ladder") != std::string::npos && !bHammer)
	{
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
		/*Switch the frame to hammer mode*/
		ScoreManager::getInstance()->addScore(500);
		changeSpriteState("hammer_sheet");
		return;
	}

	/*Platform collision with player*/
	if (object->getName().find("level1Map") != std::string::npos)
	{
		//std::cout << "Player: Collided with " << object->getName() << "\n";

		Collider* playerCollider = dynamic_cast<Collider*>(this->findComponentByType(AComponent::Physics, "PlayerCollider"));
		std::vector<AComponent*> platformColliders = object->getComponentsOfType(AComponent::Physics);
		bool hasLanded = false;

		for (AComponent* component : platformColliders) {
			Collider* platformCollider = dynamic_cast<Collider*>(component);
			if (platformCollider && platformCollider->hasCollisionWith(playerCollider)) {
				//std::cout << "Found colliding platform: " << platformCollider->getName() << std::endl;

				sf::FloatRect playerBounds = playerCollider->getGlobalBounds();
				sf::FloatRect platformBounds = platformCollider->getGlobalBounds();

				float playerBottom = playerBounds.top + playerBounds.height;
				float previousPlayerBottom = previousPosition.y + (playerBounds.height / 2.0f);
				bool collidingFromAbove = (playerBottom >= platformBounds.top - 4.0f);
					//&& previousPlayerBottom <= platformBounds.top + 4.0f);

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
					// std::cout << "Not really colliding from above tho" << std::endl;
					
					bool movingUpward = velocity.y < 0;  // Using velocity instead of position comparison
					if (movingUpward && playerBottom >= platformBounds.top - 4.0f) {
						// We're moving up and have reached/passed the platform top - treat it like landing
						// std::cout << "still going to insert it anyways" << std::endl;
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
			// std::cout << "No longer colliding with platform: " << platform->getName() << std::endl;
			if (platformsCollidingWith.empty()) {
				bGrounded = false;
				// std::cout << "Player is no longer grounded" << std::endl;
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

