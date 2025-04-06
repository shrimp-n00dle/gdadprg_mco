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
		offset.x += SPEED_MULTIPLIER;
		player->frameSprite->setScale(-2.0f, 2.0f);
		playerTransformable->move(offset * deltaTime.asSeconds());

		/*Adding walking effects*/
		if (player->getSheetName() == "walk_sheet")
		{
			SFXManager::getInstance()->mAudioList[0]->stopSong();
			//if its currenlty playing dont play it again
			if (SFXManager::getInstance()->mAudioList[4]->getSong()->getStatus() != 2)SFXManager::getInstance()->mAudioList[4]->playSong();

		}
	
	}

	else if (inputController->isLeft())
	{
		offset.x -= SPEED_MULTIPLIER;
		player->frameSprite->setScale(2.0f, 2.0f);
		playerTransformable->move(offset * deltaTime.asSeconds());

		/*Adding walking effects*/
		if (player->getSheetName() == "walk_sheet")
		{
			SFXManager::getInstance()->mAudioList[0]->stopSong();
			//if its currenlty playing dont play it again
			if (SFXManager::getInstance()->mAudioList[4]->getSong()->getStatus() != 2)SFXManager::getInstance()->mAudioList[4]->playSong();

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
			SFXManager::getInstance()->mAudioList[3]->playSong();
		}

	}	

	if (!inputController->isJump()) {
		bHop = false;
	}
	
	player->getCollider()->setLocalBounds(player->frameSprite->getGlobalBounds());

	/*If im hit*/
	if (player->getSheetName() == "hit_sheet")
	{
		SFXManager::getInstance()->mAudioList[4]->stopSong();
		//if its currenlty playing dont play it again
		if (SFXManager::getInstance()->mAudioList[1]->getSong()->getStatus() != 2)SFXManager::getInstance()->mAudioList[1]->playSong();

	}


	}

