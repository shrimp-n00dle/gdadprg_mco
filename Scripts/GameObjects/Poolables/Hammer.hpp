#pragma once
#include "../APoolable.hpp"
#include "../../Managers/TextureManager.hpp"
#include "../../Components/HammerBehaviour.hpp"
#include "../../Components/HammerHandler.hpp"
#include "../Listeners/CollisionListener.hpp"
#include "../../Managers/PhysicsManager.hpp"
#include "../../Managers/ObjectPoolHolder.hpp"
#include "GameObjectPool.hpp"
class Hammer : public APoolable, public CollisionListener
{
public:
	Hammer(std::string name);
	~Hammer();
	void initialize();

	void onRelease();
	void onActivate();
	APoolable* clone();

	void onCollisionEnter(AGameObject* object);
	void onCollisionExit(AGameObject* object);

private:
	int counter = 0;
	sf::Sprite* sprite; //= new sf::Sprite();
	float timer = 10.0f;

	const int SPAWN_RANGE = 300;

	Collider* collider;
};

