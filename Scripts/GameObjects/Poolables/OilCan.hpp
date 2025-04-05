#pragma once
#include "../APoolable.hpp"
#include "../../Managers/TextureManager.hpp"
#include "../Listeners/CollisionListener.hpp"
#include "../../Managers/PhysicsManager.hpp"
#include "../../Managers/ObjectPoolHolder.hpp"
#include "../../Components/FrameComponents/CBehaviour.hpp"
#include "GameObjectPool.hpp"
class OilCan : public APoolable, public CollisionListener
{
public:
	OilCan(std::string name);
	~OilCan();
	void initialize();
	void update(sf::Time deltaTime);
	void onRelease();
	void onActivate();
	APoolable* clone();

	void onCollisionEnter(AGameObject* object);
	void onCollisionExit(AGameObject* object);
	sf::Sprite* frameSprite;
	float timer = 1.0f;
};

