#include "MCOPlayerMovement.hpp"


MCOPlayerMovement::MCOPlayerMovement(std::string name) : AComponent(name, Script)
{

}

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
		if (inputController->isUp())
		{
			offset.y -= SPEED_MULTIPLIER;
			playerTransformable->move(offset * deltaTime.asSeconds());
		}

		else if (inputController->isDown())
		{
			offset.y += SPEED_MULTIPLIER;
			playerTransformable->move(offset * deltaTime.asSeconds());
		}

	}

	if (inputController->isRight())
	{
		offset.x += SPEED_MULTIPLIER;
		player->frameSprite->setScale(-2.0f, 2.0f);
		playerTransformable->move(offset * deltaTime.asSeconds());
	}

	else if (inputController->isLeft())
	{
		offset.x -= SPEED_MULTIPLIER;
		player->frameSprite->setScale(2.0f, 2.0f);
		playerTransformable->move(offset * deltaTime.asSeconds());
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
			//SFXManager::getInstance()->mAudioList[0]->playSong();

			// player->changeSpriteState("jump_sheet");
		}
	}

	if (!inputController->isJump()) {
		bHop = false;
	}
	
	player->getCollider()->setLocalBounds(player->frameSprite->getGlobalBounds());
	}

