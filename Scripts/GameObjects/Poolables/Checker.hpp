#pragma once
#include "../APoolable.hpp"
#include "../../Managers/TextureManager.hpp"
#include "../Listeners/CollisionListener.hpp"
#include "../../Managers/PhysicsManager.hpp"
#include "../../Managers/ObjectPoolHolder.hpp"
#include "GameObjectPool.hpp"
class Checker : public APoolable, public CollisionListener
{
public:
	Checker(std::string name);
	~Checker();
	void initialize();

	void onRelease();
	void onActivate();
	APoolable* clone();

	void onCollisionEnter(AGameObject* object);
	void onCollisionExit(AGameObject* object);
	sf::RectangleShape* checkerSprite;

private:
	int counter = 0;

	float timer = 10.0f;

	const int SPAWN_RANGE = 300;

	Collider* collider;
};

