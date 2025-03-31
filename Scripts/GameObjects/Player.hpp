#pragma once
#include "iostream"
#include "AGameObject.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/PhysicsManager.hpp"
#include "../Inputs/MCOPlayerInput.hpp"
#include "../Components/MCOPlayerMovement.hpp"
#include "../Components/FrameComponents/WalkBehaviour.hpp"
#include "../Components/FrameComponents/LadderBehaviour.hpp"
#include "../GameObjects/Poolables/GameObjectPool.hpp"


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

	bool bLadder = false;
	bool bHammer = false;

	Collider* getCollider();
	std::string getSheetName();

	sf::Sprite* frameSprite;
private:
	const float SPEED_MULTIPLIER = 300.0f;
	std::string sheetName = "";
	Collider* collider = nullptr;

	sf::Time deltaTime;
	float timer = 10.0f;

protected:
	sf::Event event;
};
