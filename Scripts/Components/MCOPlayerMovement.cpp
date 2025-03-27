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

	this->ticks += this->deltaTime.asSeconds();

	if (player->bLadder)
	{
		if (player->isUp())
		{
			offset.y -= SPEED_MULTIPLIER;
			playerTransformable->move(offset * deltaTime.asSeconds());
		}

		else if (player->isDown())
		{
			offset.y += SPEED_MULTIPLIER;
			playerTransformable->move(offset * deltaTime.asSeconds());
		}

	}

		if (player->isRight())
		{
			offset.x += SPEED_MULTIPLIER;
			playerTransformable->move(offset * deltaTime.asSeconds());
		}

		else if (player->isLeft())
		{
			offset.x -= SPEED_MULTIPLIER;
			playerTransformable->move(offset * deltaTime.asSeconds());
		}

	}

