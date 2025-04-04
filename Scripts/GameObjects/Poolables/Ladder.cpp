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
	//PhysicsManager::getInstance()->untrackObject(this->collider);
}

void Ladder::onActivate()
{
	//PhysicsManager::getInstance()->trackObject(this->collider);
}

APoolable* Ladder::clone()
{
	APoolable* copyObj = new Ladder(name);
	return copyObj;
}
void Ladder::initialize()
{
	// --- Define Ladder colliders ---
	std::vector<sf::FloatRect> ladderBounds = 
	{
		/*Total of 9 ladders in the level*/
		{550, 640, 30, 70}, 
		{285,530,30,90}, {90,550,30,60},
		{325,430,30,100}, {550,440,30,80},
		{100,340,30,70}, {200,330,30,80},
		{550,250,30,70},
		{380,160,30,70},
	};

	std::vector<sf::RectangleShape*> boundingBoxes;

	for (const auto& bounds : ladderBounds) 
	{
		Collider* ladderCollider = new Collider("LadderCollider");
		ladderCollider->setLocalBounds(bounds);
		ladderCollider->setCollisionListener(this);
		this->attachComponent(ladderCollider);
		PhysicsManager::getInstance()->trackObject(ladderCollider);

		/* Debug Lines for the bounding boxes */
		sf::RectangleShape* boundingBox = new sf::RectangleShape();
		boundingBox->setPosition(bounds.left, bounds.top);
		boundingBox->setOrigin(0, 0);
		boundingBox->setSize(sf::Vector2f(bounds.width, bounds.height));
		boundingBox->setFillColor(sf::Color(0, 255, 0, 100));  // Semi-transparent blue
		boundingBox->setOutlineColor(sf::Color::Blue);
		boundingBox->setOutlineThickness(2);

		boundingBoxes.push_back(boundingBox);
	}

	// Attach each bounding box to a Renderer
	for (auto* box : boundingBoxes) {
		Renderer* boundingRenderer = new Renderer("LadderBounds");
		boundingRenderer->assignDrawable(box);
		this->attachComponent(boundingRenderer);
	}
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

