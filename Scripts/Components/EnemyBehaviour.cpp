#include "EnemyBehaviour.hpp"

EnemyBehaviour::EnemyBehaviour(std::string name) : AComponent(name, Script) { this->reset(); }

void EnemyBehaviour::perform()
{
	ticks += deltaTime.asSeconds();
	sf::Transformable* transformable = this->getOwner()->getTransformable();

	if (this->ticks > forwardDuration && this->movementType != Side)
	{
		int counter = (movementType + 1) % EnemyMovementType::Side + 1;
		movementType = (EnemyMovementType)counter;
	}

	if (movementType == Forward)
	{
		transformable->move(0,deltaTime.asSeconds() * SPEED_MULTIPLIER);
	}
	else if (movementType == SlowForward)
	{
		transformable->move(0, deltaTime.asSeconds() * (SPEED_MULTIPLIER / 2.0f));
	}
	else if (movementType == Side)
	{
		if (transformable->getPosition().x > Game::WINDOW_WIDTH / 2)
		{
			transformable->move(deltaTime.asSeconds() * SPEED_MULTIPLIER * 1.5, 0);
		}
		else
		{
			transformable->move(-deltaTime.asSeconds() * SPEED_MULTIPLIER * 1.5,0);
		}
	}

	//check if position is out of bounds, we can delete/return to pool
	if (transformable->getPosition().x > Game::WINDOW_WIDTH + 20 || transformable->getPosition().x < -20)
	{
		//GameObjectManager::getInstance()->deleteObject(this->getOwner());

		//add code to release from pool here
		ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG)->releasePoolable((APoolable*)this->getOwner());
	}
}

void EnemyBehaviour::configure(float delay)
{
	this->delay = delay;
}

void EnemyBehaviour::reset()
{
	ticks = 0.0f;
	movementType = Forward;
	forwardDuration = (rand() % 3) + 1.0f;
}
