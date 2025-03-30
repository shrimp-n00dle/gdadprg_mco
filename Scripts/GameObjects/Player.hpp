#pragma once
#include "iostream"
#include "AGameObject.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/PhysicsManager.hpp"
#include "../Inputs/MCOPlayerInput.hpp"
#include "../Components/MCOPlayerMovement.hpp"
#include "../Components/FrameComponents/WalkBehaviour.hpp"
#include "../Components/FrameComponents/LadderBehaviour.hpp"


class Player : public AGameObject, public CollisionListener
{
public:
	Player(std::string name);
	void initialize();
	void processInput(sf::Event event);
	void update();

	void onCollisionEnter(AGameObject* object);
	void onCollisionExit(AGameObject* object);

	void changeSpriteState(std::string textureName);

	bool bLadder;

	Collider* getCollider();

	sf::Sprite* frameSprite;
private:
	//MCOPlayerMovement* movement;
	const float SPEED_MULTIPLIER = 300.0f;

	Collider* collider = nullptr;

protected:
	sf::Event event;
};
