#pragma once
#include "iostream"
#include "set"
#include "AGameObject.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/PhysicsManager.hpp"
#include "../Inputs/MCOPlayerInput.hpp"
#include "../Components/MCOPlayerMovement.hpp"
#include "../Components/FrameComponents/WalkBehaviour.hpp"
#include "../Components/FrameComponents/LadderBehaviour.hpp"
#include "../Components/HammerBehaviour.hpp"
#include "../Components/FrameComponents/HitBehaviour.hpp"
#include "../GameObjects/Poolables/GameObjectPool.hpp"
#include "UI/ResultScreen.hpp"


class Player : public AGameObject, public CollisionListener
{
public:
	Player(std::string name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

	void onCollisionEnter(AGameObject* object);
	void onCollisionExit(AGameObject* object);

	void changeSpriteState(std::string textureName);

	bool bLadder = false;
	bool bHammer = false;
	bool bGrounded = false;
	bool isGrounded() const { return bGrounded; }

	Collider* getCollider();
	std::string getSheetName();

	sf::Sprite* frameSprite;
	sf::Vector2f velocity;
	std::set<Collider*> platformsCollidingWith;

	float hitTimer = 0.2f;
	float hammerTimer = 0.2f;

	// Passive score generation
	float passiveScoreTimer = 0.0f;
	const float PASSIVE_SCORE_INTERVAL = 5.0f; // 5 seconds
	const int PASSIVE_SCORE_AMOUNT = 500;      // 500 points

private:
	const float SPEED_MULTIPLIER = 300.0f;
	std::string sheetName = "";
	Collider* collider = nullptr;


	sf::Time deltaTime;
	float timer = 10.0f;
	float mainOffset;
	sf::Vector2f previousPosition = sf::Vector2f(0,0);
	sf::Time debugTimer = sf::Time::Zero;  // Timer for debug output
	

protected:
	sf::Event event;
};