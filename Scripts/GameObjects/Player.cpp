#include "Player.hpp"

Player::Player(std::string name) : AGameObject(name), CollisionListener()
{
	this->name = name;
}

void Player::initialize()
{
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTexture("player"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
	this->transformable.setPosition(640.0f / 2, 480.0f / 2);

	Renderer* renderer = new Renderer("MCOPlayerSprite");
	renderer->assignDrawable(this->sprite);
	attachComponent(renderer);

	MCOPlayerInput* inputController = new MCOPlayerInput("MCOPlayerInput");
	this->attachComponent(inputController);

	MCOPlayerMovement* movement = new MCOPlayerMovement("MCOMovement");
	this->attachComponent(movement);

	/*Add colliders*/
	this->collider = new Collider("PlayerCollider");
	this->collider->setLocalBounds(sprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(this->collider);

	PhysicsManager::getInstance()->trackObject(this->collider);
}


void Player::processInput(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		keyFlag = true;
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		keyFlag = false;
	}

	switch (event.key.code)
	{
	case sf::Keyboard::W:
		moveUp = keyFlag;
		break;
	case sf::Keyboard::A:
		moveLeft = keyFlag;
		break;
	case sf::Keyboard::S:
		moveDown = keyFlag;
		break;
	case sf::Keyboard::D:
		moveRight = keyFlag;
		break;
	}
}

void Player::update() {}

bool Player::isUp() { return moveUp; }
bool Player::isDown() { return moveDown; }
bool Player::isLeft() { return moveLeft; }
bool Player::isRight() { return moveRight; }

void Player::onCollisionEnter(AGameObject* object)
{
	std::cout << "Player Collision" << std::endl;
	/*Eliminate player*/
	//if (object->getName().find("barrel") != std::string::npos)
	//{
		//std::cout << "Player: Collided with " << object->getName() << "\n";
		//return;
	//}

	//if (object->getName().find("enemy") != std::string::npos)
	//{
		//std::cout << "Player: Collided with " << object->getName() << "\n";
		//return;
	//}

	/*Ladder collision with player*/
	if (object->getName().find("ladder") != std::string::npos)
	{
		std::cout << "Player: Collided with " << object->getName() << "\n";
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
	bLadder = false;
}

