#pragma once
#include "../APoolable.hpp"
#include "../../Managers/TextureManager.hpp"
#include "../Listeners/CollisionListener.hpp"
#include "../../Managers/PhysicsManager.hpp"
#include "../../Managers/ObjectPoolHolder.hpp"
#include "../../Components/FrameComponents/PBehaviour.hpp"
#include "GameObjectPool.hpp"
class Princess : public APoolable, public CollisionListener
{
public:
	Princess(std::string name);
	~Princess();
	void initialize();
	void update(sf::Time deltaTime);
	void onRelease();
	void onActivate();
	APoolable* clone();

	void onCollisionEnter(AGameObject* object);
	void onCollisionExit(AGameObject* object);
	sf::Sprite* frameSprite;
	float timer = 2.0f;
};

