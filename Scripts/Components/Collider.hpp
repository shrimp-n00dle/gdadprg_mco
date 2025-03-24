#pragma once
#include "AComponent.hpp"
#include "SFML/Graphics.hpp"
#include "unordered_set"
#include "../GameObjects/Listeners/CollisionListener.hpp"
#include "../GameObjects/AGameObject.hpp"
class Collider : public AComponent
{
public:
	Collider(std::string name);

	void setCollisionListener(CollisionListener* listener);

	
	//void setChecked(bool flag);
	//bool isChecked();


	bool willCollide(Collider* other);
	bool hasCollisionWith(Collider* other);
	void addCollision(Collider* other);
	void removeCollision(Collider* other);

	//bool alreadyCollided();
	//void setAlreadyCollided(bool flag);

	sf::FloatRect getGlobalBounds();
	void setLocalBounds(sf::FloatRect localBounds);
	void collisionEnter(AGameObject* gameObjects);
	void collisionExit(AGameObject* gameObjects);

	void perform();
	void clearCollisions();

private:
	//bool collided = false;
	std::unordered_set<Collider*> collisions;

	bool checked = false;
	sf::FloatRect localBounds;
	CollisionListener* listener;
};

