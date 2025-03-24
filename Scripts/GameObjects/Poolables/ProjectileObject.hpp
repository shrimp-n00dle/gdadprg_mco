#pragma once
#include "../APoolable.hpp"
#include "../Listeners/CollisionListener.hpp"
#include "../../Components/ProjectileMovement.hpp"
#include "../../Components/Collider.hpp"
#include "../../Managers/TextureManager.hpp"
#include "../../Managers/PhysicsManager.hpp"
#include "../AirplanePlayer.hpp"

class ProjectileObject : public APoolable, public CollisionListener
{
public:
	ProjectileObject(std::string name);
	void initialize();
	void onRelease();
	void onActivate();
	
	APoolable* clone();

	void onCollisionEnter(AGameObject* object);
	void onCollisionExit(AGameObject* object);
private:
	ProjectileMovement* projectileMovement = nullptr;
	Collider* collider = nullptr;
	bool hasHit = false;
};

