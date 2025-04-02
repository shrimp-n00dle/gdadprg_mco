#pragma once
#include "../GameObjects/AGameObject.hpp"
#include "../Components/AComponent.hpp"
#include "../Components/Collider.hpp"

typedef std::vector<Collider*> CollisionList;

class PhysicsManager : public AComponent
{
public:
	static void initialize(std::string name, AGameObject* parent);
	static PhysicsManager* getInstance();

	void trackObject(Collider* object);
	void untrackObject(Collider* object);
	void perform();

	void debugCollisions();

private:
	PhysicsManager(std::string name) : AComponent(name, Script) {};
	PhysicsManager(PhysicsManager const&) : AComponent(name, Script) {};
	PhysicsManager& operator=(PhysicsManager const&) {}; //assignment operator is 
	static PhysicsManager* sharedInstance;

	CollisionList trackedObjects;
	CollisionList forCleaningObjects;

	void cleanUpObjects();

};

