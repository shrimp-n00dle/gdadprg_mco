#include "Player.hpp"

Player::Player(std::string name) : AGameObject(name), CollisionListener()
{
	this->name = name;
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
	std::cout << "Player Collision" << std::endl;

	/*Eliminate player*/
	//if (object->getName().find("barrel") != std::string::npos)
	//{
		//std::cout << "Player: Collided with " << object->getName() << "\n";
		//return;
	//}
	
	/*Attacked by fireballs*/
	//if (object->getName().find("enemy") != std::string::npos)
	//{
		//std::cout << "Player: Collided with " << object->getName() << "\n";
		//return;
	//}

	std::cout << object->getName() << std::endl;

	/*Ladder collision with player*/
	if (object->getName().find("ladder") != std::string::npos)
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
		this->attachChild(object);
		return;
	}


}

void Player::onCollisionExit(AGameObject* object)
{
	std::cout << "Collision Exit" << std::endl;
	if (bLadder) changeSpriteState("walk_sheet");
	bLadder = false;
	
}

void Player::changeSpriteState(std::string textureName)
{

	/*Reassign the sprite*/
	frameSprite->setTexture(*TextureManager::getInstance()->getTexture(textureName));
	sf::Vector2u textureSize = frameSprite->getTexture()->getSize();
	frameSprite->setScale(2.0f, 2.0f);

	Renderer* renderer = new Renderer("MCOPlayerSprite");
	renderer->assignDrawable(frameSprite);
	attachComponent(renderer);

	/*Rewrite collider*/
	this->collider->setLocalBounds(frameSprite->getGlobalBounds());
}

Collider* Player::getCollider()
{
	return this->collider;
}

