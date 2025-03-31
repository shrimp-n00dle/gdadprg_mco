#include "Player.hpp"

Player::Player(std::string name) : AGameObject(name), CollisionListener()
{
	this->name = name;
	this->sheetName = "walk_sheet";

}

void Player::initialize()
{
	frameSprite = new sf::Sprite();
	frameSprite->setTexture(*TextureManager::getInstance()->getTexture("walk_sheet"));
	sf::Vector2u textureSize = frameSprite->getTexture()->getSize();
	//this->sprite->setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
	//this->transformable.setPosition(400.0f,80.0f);
	frameSprite->setScale(2.0f, 2.0f);

	Renderer* renderer = new Renderer("MCOPlayerSprite");
	renderer->assignDrawable(frameSprite);
	attachComponent(renderer);

	setChildPosition(400.0f, 60.0f);

	MCOPlayerInput* inputController = new MCOPlayerInput("MCOPlayerInput");
	this->attachComponent(inputController);

	MCOPlayerMovement* movement = new MCOPlayerMovement("MCOMovement");
	this->attachComponent(movement);

	WalkBehaviour* walkBehaviour = new WalkBehaviour("WalkBehaviour");
	this->attachComponent(walkBehaviour);

	LadderBehaviour* ladderBehaviour = new LadderBehaviour("LadderBehaviour");
	this->attachComponent(ladderBehaviour);

	HammerBehaviour* hammerBehaviour = new HammerBehaviour("HammerBehaviour");
	this->attachComponent(hammerBehaviour);

	/*Add colliders*/
	this->collider = new Collider("PlayerCollider");
	this->collider->setLocalBounds(frameSprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(this->collider);

	PhysicsManager::getInstance()->trackObject(this->collider);
}

void Player::processInput(sf::Event event) 
{
	AGameObject::processInput(event);
}

void Player::update() {}

void Player::onCollisionEnter(AGameObject* object)
{
	/*Eliminate player*/
	if (object->getName().find("barrel") != std::string::npos)
	{
		std::cout << "Player: Collided with " << object->getName() << "\n";
		//changeSpriteState("hit_sheet");
		return;
	}

	/*If the player has a hammer, delete the barrel*/
	if (object->getName().find("barrel") != std::string::npos && bHammer)
	{
		std::cout << "Player: Collided with " << object->getName() << "\n";
		return;
	}
	
	/*Attacked by fireballs and no hammer*/
	if (object->getName().find("enemy") != std::string::npos && !bHammer)
	{
		std::cout << "Player: Collided with " << object->getName() << "\n";
		//changeSpriteState("hit_sheet");
		return;
	}

	/*Attacked by fireballs with hammer*/
	if (object->getName().find("enemy") != std::string::npos && bHammer)
	{
		std::cout << "Player: Collided with " << object->getName() << "\n";
		return;
	}

	/*Ladder collision with player*/
	if (object->getName().find("ladder") != std::string::npos && !bHammer)
	{
		std::cout << "Player: Collided with " << object->getName() << "\n";
		/*Ladder Behaviour initialized the sprite*/
		if (!bLadder)
		{
			changeSpriteState("climb_sheet");
		}
		bLadder = true;
		return;
	}

	/*Hammer collision with player*/
	if (object->getName().find("hammer") != std::string::npos)
	{
		std::cout << "Player: Collided with " << object->getName() << "\n";

		/*Switch the frame to hammer mode*/
		changeSpriteState("hammer_sheet");
		return;
	}
}

void Player::onCollisionExit(AGameObject* object)
{
	bLadder = false;
}

void Player::changeSpriteState(std::string textureName)
{
	sheetName = textureName;
	/*Change to hammer_sheet after testing*/
	if (textureName == "hammer_sheet")
	{
		/*Player will not change sprite while hammer mode is still engaged*/
		bHammer = true;
	}

	/*Reassign the sprite*/
	frameSprite->setTexture(*TextureManager::getInstance()->getTexture(textureName));
	sf::Vector2u textureSize = frameSprite->getTexture()->getSize();
	frameSprite->setScale(2.0f, 2.0f);

	Renderer* renderer = new Renderer("MCOPlayerSprite");
	renderer->assignDrawable(frameSprite);
	attachComponent(renderer);

	/*Reassign collider*/
	this->collider->setLocalBounds(frameSprite->getGlobalBounds());
}

Collider* Player::getCollider()
{
	return this->collider;
}

std::string Player::getSheetName()
{
	return sheetName;
}

