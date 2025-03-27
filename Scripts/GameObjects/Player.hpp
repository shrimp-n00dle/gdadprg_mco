#pragma once
#include "iostream"
#include "AGameObject.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/PhysicsManager.hpp"
#include "../Inputs/MCOPlayerInput.hpp"
#include "../Components/MCOPlayerMovement.hpp"


class Player : public AGameObject, public CollisionListener
{
public:
	Player(std::string name);
	void initialize();
	void processInput(sf::Event event);
	void update();

	void onCollisionEnter(AGameObject* object);
	void onCollisionExit(AGameObject* object);

	bool isUp();
	bool isDown();
	bool isLeft();
	bool isRight();
	bool bLadder;
private:
	//MCOPlayerMovement* movement;
	const float SPEED_MULTIPLIER = 300.0f;


	Collider* collider = nullptr;
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
	bool keyFlag = false;

protected:
	sf::Event event;
};
