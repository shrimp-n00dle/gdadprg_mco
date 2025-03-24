#pragma once
#include "../APoolable.hpp"
#include "../../Managers/TextureManager.hpp"
#include "../../Components/EnemyBehaviour.hpp"
#include "../Listeners/CollisionListener.hpp"
#include "../../Managers/PhysicsManager.hpp"
class EnemyAirplane : public APoolable, public CollisionListener
{
public:
	EnemyAirplane(std::string name);
	~EnemyAirplane();
	void initialize();

	void onRelease();
	void onActivate();
	APoolable* clone();

	void onCollisionEnter(AGameObject* object);
	void onCollisionExit(AGameObject* object);

private:
	sf::Sprite* sprite = new sf::Sprite();
	int counter = 0;

	const int SPAWN_RANGE = 300;

	Collider* collider;
};

