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

	// Handle hit delay and scene transition
	if (bHasHit)
	{
		hitDelay += deltaTime.asSeconds();
		SFXManager::getInstance()->stopBGM();
		if (hitDelay >= HIT_SOUND_DURATION)
		{
			// Reset hit state
			hitDelay = 0.0f;

			// Return to main menu
			SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);
			return; // Exit early to prevent further movement
		}
		return;
	}

	/*If im hit*/
	if (player->getSheetName() == "hit_sheet")
	{
		bHasHit = true;
		hitDelay = 0.0f;
		SFXManager::getInstance()->stopSound(AudioKeys::WALKING);
		SFXManager::getInstance()->stopBGM();
		if (!SFXManager::getInstance()->isSoundPlaying(AudioKeys::HIT))
		{
			SFXManager::getInstance()->setLoop(AudioKeys::HIT, false);
			SFXManager::getInstance()->playSound(AudioKeys::HIT);
		}
		return;
	}

	sf::Vector2f offset(0.0f, 0.0f);
	sf::Vector2f jumpOffset(0.0f, 0.0f);

	this->ticks += this->deltaTime.asSeconds();

	/*If the player is at the ladder*/
	if (player->bLadder && !bHasHit)
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

	/*If the player wants to move to the right/left*/
	if (inputController->isRight() && !bHasHit)
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
	else if (inputController->isLeft() && !bHasHit)
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

	if (!player->bLadder && !player->bHammer && !bHasHit)
	{
		if (inputController->isJump() && !bHop && player->isGrounded()
			&& player->getSheetName() != "hit_sheet")
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

	// Stop walking sound when hammer is active
	if (player->bHammer && !bHasHit)
	{
		SFXManager::getInstance()->stopSound(AudioKeys::WALKING);
		SFXManager::getInstance()->pauseBGM();
		if (!SFXManager::getInstance()->isSoundPlaying(AudioKeys::HAMMER))
		{
			SFXManager::getInstance()->playSound(AudioKeys::HAMMER);
		}
	}
	else if (!bHasHit)  // Only play BGM if not in hit state
	{
		SFXManager::getInstance()->playBGM();
	}
}

