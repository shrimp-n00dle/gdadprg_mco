#include "PlayerMovement.hpp"


PlayerMovement::PlayerMovement(std::string name) : AComponent(name,Script)
{

}

void PlayerMovement::perform()
{

	AirplanePlayer* airplanePlayer = (AirplanePlayer*)this->getOwner();
	//PlayerInput* inputController = (PlayerInput*)(airplanePlayer->getComponentsOfType(ComponentType::Input)[0]);
	sf::Transformable* playerTransformable = airplanePlayer->getTransformable();

	if (playerTransformable == nullptr /* || inputController == nullptr*/)
	{
		std::cout << "playerTransformable not found" << std::endl;
	}

	sf::Vector2f offset(0.0f,0.0f);

	this->ticks += this->deltaTime.asSeconds();
	if (airplanePlayer->hasFired() && this->ticks > this->BULLET_SPAWN_INTERVAL)
	{
		this->projectilePool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::PROJECTILE_POOL_TAG);
		this->ticks = 0.0f;
		this->projectilePool->requestPoolable();
	}

	if (airplanePlayer->isUp())
	{
		offset.y -= SPEED_MULTIPLIER;
		playerTransformable->move(offset * deltaTime.asSeconds());
	}

	else if (airplanePlayer->isDown())
	{
		offset.y += SPEED_MULTIPLIER;
		playerTransformable->move(offset * deltaTime.asSeconds());
	}

	else if (airplanePlayer->isRight())
	{
		offset.x += SPEED_MULTIPLIER;
		playerTransformable->move(offset * deltaTime.asSeconds());
	}

	else if (airplanePlayer->isLeft())
	{
		offset.x -= SPEED_MULTIPLIER;
		playerTransformable->move(offset * deltaTime.asSeconds());
	}


}