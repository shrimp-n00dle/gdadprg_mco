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

void Player::update(sf::Time deltaTime) {
	// std::cout << "kyaaaa~~" << std::endl;
	if (!bGrounded) {  // Apply gravity only when not grounded
		velocity.y += 9.8f * deltaTime.asSeconds() * 0.5f;
	}
	frameSprite->move(0, velocity.y);

	AGameObject::update(deltaTime);
}

void Player::onCollisionEnter(AGameObject* object)
{
	/*Eliminate player*/
	//if (object->getName().find("barrel") != std::string::npos)
	//{
		//std::cout << "Player: Collided with " << object->getName() << "\n";
		//return;
	//}

	std::cout << "object->getName() = " << object->getName() << std::endl;
	
	/*Attacked by fireballs and no hammer*/
	if (object->getName().find("enemy") != std::string::npos && !bHammer)
	{
		std::cout << "Player: Collided with " << object->getName() << "\n";
		//changeSpriteState("hit_sheet");
		return;
	}

	std::cout << object->getName() << std::endl;

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
		//changeSpriteState("hammer_sheet");
		return;
	}

	/*Platform collision with player*/
	if (object->getName().find("level1Map") != std::string::npos)
	{
		velocity.y = 0.f;
		bGrounded = true;  // Ensure player is considered grounded

		platformsCollidingWith.insert(object);

		sf::FloatRect bounds = frameSprite->getGlobalBounds();
		frameSprite->move(0, -2.f);

		return;
	}
}

void Player::onCollisionExit(AGameObject* object)
{
	if (object->getName().find("ladder") != std::string::npos)
	{
		changeSpriteState("walk_sheet");
		bLadder = false;
	}

	if (object->getName().find("level1Map") != std::string::npos)
	{
		platformsCollidingWith.erase(object);

		if (platformsCollidingWith.empty())
		{
			bGrounded = false;
		}
	}
}

void Player::changeSpriteState(std::string textureName)
{
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

