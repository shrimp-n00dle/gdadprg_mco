#pragma once
#include "iostream"
#include "AGameObject.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/PhysicsManager.hpp"
#include "../Inputs/PlayerInput.hpp"
#include "../Components/PlayerMovement.hpp"


class AirplanePlayer : public AGameObject, public CollisionListener
{
public:
	AirplanePlayer(std::string name);
	void initialize();
	void processInput(sf::Event event);
	void update();

	void onCollisionEnter(AGameObject* object);
	void onCollisionExit(AGameObject* object);

	bool isUp();
	bool isDown();
	bool isLeft();
	bool isRight();
	bool hasFired();

private:
	const float SPEED_MULTIPLIER = 300.0f;

	
	Collider* collider;
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
	bool keyFlag = false;
	bool fire = false;

protected:
	sf::Event event;
};
