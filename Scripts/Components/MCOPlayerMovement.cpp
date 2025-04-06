#include "MCOPlayerMovement.hpp"


MCOPlayerMovement::MCOPlayerMovement(std::string name) : AComponent(name, Script) {}

void MCOPlayerMovement::perform()
{
	Player* player = (Player*)this->getOwner();
	MCOPlayerInput* inputController = (MCOPlayerInput*)(player->getComponentsOfType(ComponentType::Input)[0]);
	sf::Transformable* playerTransformable = player->getTransformable();

	if (playerTransformable == nullptr || inputController == nullptr)
	{
		std::cout << "playerTransformable not found" << std::endl;
	}

	sf::Vector2f offset(0.0f, 0.0f);
	sf::Vector2f jumpOffset(0.0f, 0.0f);

	this->ticks += this->deltaTime.asSeconds();

	if (player->bLadder)
	{
		player->velocity = sf::Vector2f(0.0f, 0.0f);
		if (inputController->isUp())
		{
			offset.y -= SPEED_MULTIPLIER * 0.3f;
			playerTransformable->move(offset * deltaTime.asSeconds());
		}

		else if (inputController->isDown())
		{
			offset.y += SPEED_MULTIPLIER * 0.3f;
			playerTransformable->move(offset * deltaTime.asSeconds());
		}
		offset = sf::Vector2f(0.0f, 0.0f);
	}
	if (inputController->isRight())
	{
		if (player->bLadder) offset.x += SPEED_MULTIPLIER * 0.3f;
		else offset.x += SPEED_MULTIPLIER;
		player->frameSprite->setScale(-2.0f, 2.0f);
		playerTransformable->move(offset * deltaTime.asSeconds());

		/*Adding walking effects*/
		if (player->getSheetName() == "walk_sheet" && !SFXManager::getInstance()->isSoundPlaying(AudioKeys::WALKING))
		{
			SFXManager::getInstance()->playSound(AudioKeys::WALKING);
		}
	}
	else if (inputController->isLeft())
	{
		if (player->bLadder) offset.x -= SPEED_MULTIPLIER * 0.3f;
		else offset.x -= SPEED_MULTIPLIER;
		player->frameSprite->setScale(2.0f, 2.0f);
		playerTransformable->move(offset * deltaTime.asSeconds());

		/*Adding walking effects*/
		if (player->getSheetName() == "walk_sheet" && !SFXManager::getInstance()->isSoundPlaying(AudioKeys::WALKING))
		{
			SFXManager::getInstance()->playSound(AudioKeys::WALKING);
		}
	}

	if (!player->bLadder && !player->bHammer)
	{
		if (inputController->isJump() && !bHop && player->isGrounded())
		{
			std::cout << "Jump initiated" << std::endl;
			player->bGrounded = false;
			player->platformsCollidingWith.clear();
			player->velocity.y -= JUMP_MULTIPLIER; // Upward force
			bHop = true;

			/*Adding jumping effects*/
			SFXManager::getInstance()->playSound(AudioKeys::JUMPING);
		}

	}	

	if (!inputController->isJump()) {
		bHop = false;
	}
	
	player->getCollider()->setLocalBounds(player->frameSprite->getGlobalBounds());

	/*If im hit*/
	if (player->getSheetName() == "hit_sheet")
	{
		SFXManager::getInstance()->stopSound(AudioKeys::WALKING);
		if (!SFXManager::getInstance()->isSoundPlaying(AudioKeys::HIT))
		{
			SFXManager::getInstance()->playSound(AudioKeys::HIT);
		}
	}

	// Stop walking sound when hammer is active
	if (player->bHammer)
	{
		SFXManager::getInstance()->stopSound(AudioKeys::WALKING);
		if (!SFXManager::getInstance()->isSoundPlaying(AudioKeys::HAMMER))
		{
			SFXManager::getInstance()->playSound(AudioKeys::HAMMER);
		}
	}

	// Play hit sound
	if (player->getSheetName() == "hit_sheet")
	{
		SFXManager::getInstance()->stopSound(AudioKeys::WALKING);
		if (!SFXManager::getInstance()->isSoundPlaying(AudioKeys::HIT))
		{
			SFXManager::getInstance()->playSound(AudioKeys::HIT);
		}
	}
}

