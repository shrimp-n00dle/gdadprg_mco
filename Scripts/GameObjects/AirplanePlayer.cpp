#include "AirplanePlayer.hpp"

AirplanePlayer::AirplanePlayer(std::string name) : AGameObject(name) , CollisionListener()
{
	this->name = name;
}

void AirplanePlayer::initialize()
{
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTexture("eagle"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
	this->transformable.setPosition(640.0f/2,480.0f/2);

	Renderer* renderer = new Renderer("PlayerSprite");
	renderer->assignDrawable(this->sprite);
	attachComponent(renderer);

	PlayerInput* inputController = new PlayerInput("MyPlayerInput");
	this->attachComponent(inputController);

	PlayerMovement* movement = new PlayerMovement("MyMovement");
	this->attachComponent(movement);

	/*Add colliders*/
	this->collider = new Collider("PlaneCollider");
	this->collider->setLocalBounds(sprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(this->collider);

	PhysicsManager::getInstance()->trackObject(this->collider);

}


void AirplanePlayer::processInput(sf::Event event) 
{
	if(event.type == sf::Event::KeyPressed)
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
	case sf::Keyboard::Space:
		this->fire = keyFlag;
		break;
	}
}

void AirplanePlayer::update() {}

bool AirplanePlayer::isUp() { return moveUp; }
bool AirplanePlayer::isDown() { return moveDown; }
bool AirplanePlayer::isLeft() { return moveLeft; }
bool AirplanePlayer::isRight() { return moveRight; }
bool AirplanePlayer::hasFired() { return this->fire; }

void AirplanePlayer::onCollisionEnter(AGameObject* object)
{
	if (object->getName().find("enemy") != std::string::npos)
	{
		std::cout << "AIRPLANe pLAter: Collided with " << object->getName() << "\n";
		return;
	}
}

void AirplanePlayer::onCollisionExit(AGameObject* object)
{

}

