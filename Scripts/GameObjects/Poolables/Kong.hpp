#pragma once
#include "../APoolable.hpp"
#include "../../Managers/TextureManager.hpp"
#include "../Listeners/CollisionListener.hpp"
#include "../../Managers/PhysicsManager.hpp"
#include "../../Managers/ObjectPoolHolder.hpp"
#include "../../Components/FrameComponents/KBehaviour.hpp"
#include "GameObjectPool.hpp"
class Kong : public APoolable, public CollisionListener
{
public:
	Kong(std::string name);
	~Kong();
	void initialize();
	void update(sf::Time deltaTime);
	void onRelease();
	void onActivate();
	APoolable* clone();

	void onCollisionEnter(AGameObject* object);
	void onCollisionExit(AGameObject* object);
	sf::Sprite* frameSprite;
	float timer = 4.0f;
};

