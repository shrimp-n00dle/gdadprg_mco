#include "Collider.hpp"

Collider::Collider(std::string name): AComponent(name, AComponent::Physics)
{


}

void Collider::setCollisionListener(CollisionListener* listener)
{
	this->listener = listener;
}

//void Collider::setChecked(bool flag)
//{
//	this->checked = flag;
//}

//bool Collider::isChecked()
//{
//	return this->checked;
//}

bool Collider::willCollide(Collider* other)
{
	sf::FloatRect A = this->getGlobalBounds();
	sf::FloatRect B = other->getGlobalBounds();

	return A.intersects(B);
}

//bool Collider::alreadyCollided()
//{
//	return this->collided;
//}

//void Collider::setAlreadyCollided(bool flag)
//{
//	this->collided = flag;
//}

void Collider::setLocalBounds(sf::FloatRect localBounds)
{
	this->localBounds = localBounds;
}

void Collider::collisionEnter(AGameObject* gameObjects)
{
	if (this->listener != nullptr)
	{
		this->listener->onCollisionEnter(gameObjects);
	}
}

void Collider::collisionExit(AGameObject* gameObjects)
{
	if (this->listener != nullptr)
	{
		this->listener->onCollisionExit(gameObjects);
	}
}

sf::FloatRect Collider::getGlobalBounds()
{
	//std::cout << this->localBounds.left << ":" << this->localBounds.top << ":" << std::endl;
	return this->getOwner()->getGlobalTransform().transformRect(this->localBounds);
}

void Collider::perform()
{

}

bool Collider::hasCollisionWith(Collider* other)
{
	return this->collisions.find(other) != this->collisions.end();
}

void Collider::addCollision(Collider* other)
{
	this->collisions.insert(other);
}

void Collider::removeCollision(Collider* other)
{
	this->collisions.erase(other);
}

void Collider::clearCollisions()
{
	for (Collider* collider : this->collisions)
	{
		collider->collisionExit(this->getOwner());
		this->collisionExit(collider->getOwner());
		collider->removeCollision(this);
	}

	collisions.clear();
}