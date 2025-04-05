#pragma once
#include "../APoolable.hpp"
#include "../../Managers/TextureManager.hpp"
#include "../../Components/FrameComponents/BarrelBehaviour.hpp"
#include "../../Components/BarrelHandler.hpp"
#include "../Listeners/CollisionListener.hpp"
#include "../../Managers/PhysicsManager.hpp"
#include "../../Managers/ObjectPoolHolder.hpp"
#include "GameObjectPool.hpp"
class Barrel : public APoolable, public CollisionListener
{
public:
	Barrel(std::string name);
	~Barrel();
	void initialize();

	void update(sf::Time deltaTime);

	void onRelease();
	void onActivate();
	APoolable* clone();

	void onCollisionEnter(AGameObject* object);
	void onCollisionExit(AGameObject* object);
	sf::Sprite* frameSprite;
	bool bGrounded= false;
	bool isGrounded() const { return bGrounded; }
	sf::Vector2f velocity;
	std::set<Collider*> platformsCollidingWith;
	float barrelDirection = 1.0f;

private:

	int counter = 0;
	sf::Vector2f previousPosition = sf::Vector2f(0, 0);
	float timer = 10.0f;
	const int SPAWN_RANGE = 300;
	Collider* collider;
};

