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
	sf::RectangleShape* shape;
	bool onGround = false;
	bool bLeft = true;
	bool isGrounded() const { return onGround; }
	bool isTurn() const{ return bLeft; }
	float timer = 0.5f;

private:
	int counter = 0;
	const int SPAWN_RANGE = 300;
	Collider* collider;
};

