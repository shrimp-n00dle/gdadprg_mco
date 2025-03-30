#include "Ladder.hpp"

Ladder::Ladder(std::string name) : APoolable(name), CollisionListener()
{
};

Ladder::~Ladder()
{
	delete this->sprite;
}


void Ladder::onRelease()
{
	PhysicsManager::getInstance()->untrackObject(this->collider);
}

void Ladder::onActivate()
{

	//EnemyBehaviour* behaviour = (EnemyBehaviour*)findComponentByName("EnemyBehaviour");
	//behaviour->reset();

	//LadderBehaviour* ladderBehaviour = new LadderBehaviour("LadderBehaviour");
	//this->attachComponent(ladderBehaviour);

	PhysicsManager::getInstance()->trackObject(this->collider);

	setChildPosition(Game::WINDOW_WIDTH / 2, 0);
	getTransformable()->move(rand() % SPAWN_RANGE - rand() % SPAWN_RANGE, 50);
}

APoolable* Ladder::clone()
{
	APoolable* copyObj = new Ladder(name);
	return copyObj;
}

void Ladder::initialize()
{
	sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("ladder"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	setChildPosition(640 / 2, -30);
	getTransformable()->move(rand() % SPAWN_RANGE - rand() % SPAWN_RANGE, 0);

	Renderer* renderer = new Renderer("LadderSprite");
	renderer->assignDrawable(sprite);
	attachComponent(renderer);

	this->collider = new Collider("LadderCollider");
	this->collider->setLocalBounds(sprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(this->collider);
}

void Ladder::onCollisionEnter(AGameObject* object)
{
	if (object->getName().find("player") != std::string::npos)
	{
		std::cout << "Ladder: collided with " << object->getName() << std::endl;
		return;
	}
}
void Ladder::onCollisionExit(AGameObject* object) {}

