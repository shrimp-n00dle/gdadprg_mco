#include "PhysicsManager.hpp"

PhysicsManager* PhysicsManager::sharedInstance = nullptr;

void PhysicsManager::initialize(std::string name, AGameObject* parent)
{
	std::cout << name << "initialized!" << std::endl;
	sharedInstance = new PhysicsManager(name);
	parent->attachComponent(sharedInstance);
}

PhysicsManager* PhysicsManager::getInstance()
{
	if (!sharedInstance) {
		sharedInstance = new PhysicsManager("PhysicsManager");
	}
	return sharedInstance;
}

void PhysicsManager::trackObject(Collider* object)
{
	//object->setAlreadyCollided(false);
	this->trackedObjects.push_back(object);
}

void PhysicsManager::untrackObject(Collider* object)
{
	this->forCleaningObjects.push_back(object);
}

void PhysicsManager::perform()
{
	for (int i = 0; i < this->trackedObjects.size(); i++)
	{
		for (int j = i + 1; j < this->trackedObjects.size(); j++)
		{
			if (this->trackedObjects[i]->getOwner()->isEnabled() && this->trackedObjects[j]->getOwner()->isEnabled())
			{
				//collision check
				if (this->trackedObjects[i]->willCollide(this->trackedObjects[j]))
				{
					//handle collision enter for each one
					if (!this->trackedObjects[i]->hasCollisionWith(this->trackedObjects[j]))
					{
						this->trackedObjects[i]->addCollision(this->trackedObjects[j]);
						this->trackedObjects[i]->collisionEnter(this->trackedObjects[j]->getOwner());



					} if (!this->trackedObjects[j]->hasCollisionWith(this->trackedObjects[i]))
					{
						this->trackedObjects[j]->addCollision(this->trackedObjects[i]);
						this->trackedObjects[j]->collisionEnter(this->trackedObjects[i]->getOwner());
					}
				}
				else
				{
					//if they are not collding, check if we have to trigger collisionExit
					if (this->trackedObjects[i]->hasCollisionWith(this->trackedObjects[j]))
					{
						this->trackedObjects[i]->collisionExit(this->trackedObjects[j]->getOwner());
						this->trackedObjects[i]->removeCollision(this->trackedObjects[j]);



					} if (this->trackedObjects[j]->hasCollisionWith(this->trackedObjects[i]))
					{
						this->trackedObjects[j]->collisionExit(this->trackedObjects[i]->getOwner());
						this->trackedObjects[j]->removeCollision(this->trackedObjects[i]);
					}
				}
			}
		}
	}

	this->cleanUpObjects();
}

void PhysicsManager::debugCollisions()
{
	std::cout << "========== PHYSICS DEBUG ==========\n";
	/*
	std::cout << "Tracked objects: " << trackedObjects.size() << "\n";

	for (int i = 0; i < trackedObjects.size(); i++) {
		Collider* collider = trackedObjects[i];
		AGameObject* owner = collider->getOwner();
		sf::FloatRect bounds = collider->getGlobalBounds();

		std::cout << i << ": " << collider->getName() << " collider bounds: "
			<< bounds.left << ", " << bounds.top
			<< " size: " << bounds.width << "x" << bounds.height << "\n";

		// Print owner position
		sf::Vector2f ownerPos = owner->getTransformable()->getPosition();
		std::cout << "   Owner position: " << ownerPos.x << ", " << ownerPos.y << "\n";
	}
	*/
	// Check potential collisions
	std::cout << "----- CURRENT COLLISION CHECKS -----\n";
	for (int i = 0; i < trackedObjects.size(); i++) {
		for (int j = i + 1; j < trackedObjects.size(); j++) {
			Collider* collider1 = trackedObjects[i];
			Collider* collider2 = trackedObjects[j];

			sf::FloatRect bounds1 = collider1->getGlobalBounds();
			sf::FloatRect bounds2 = collider2->getGlobalBounds();

			bool isColliding = bounds1.intersects(bounds2);

			if (isColliding) 
				std::cout << "Check: " << collider1->getOwner()->getName()
					<< " vs " << collider2->getOwner()->getName()
					<< " - Colliding: " << (isColliding ? "YES" : "NO") << "\n";
		}
	}
	std::cout << "==================================\n";
}

void PhysicsManager::cleanUpObjects()
{
	for (int i = 0; i < this->forCleaningObjects.size(); i++)
	{
		for (int j = 0; j < this->trackedObjects.size(); j++)
		{
			if (this->forCleaningObjects[i] == this->trackedObjects[j])
			{
				this->trackedObjects.erase(this->trackedObjects.begin() + j);
			}
		}
	}

	this->forCleaningObjects.clear();
}