#include "Level1Map.hpp"

Level1Map::Level1Map(std::string name) : AGameObject(name)
{
	
}

void Level1Map::initialize()
{
	sf::Sprite* mapSprite = new sf::Sprite();
	mapSprite->setTexture(*TextureManager::getInstance()->getTexture("level1"));
	mapSprite->setScale(3.0f, 3.0f);
	sf::Vector2u textureSize = mapSprite->getTexture()->getSize();
	mapSprite->setOrigin(textureSize.x / 2.0f, textureSize.y);
	mapSprite->setPosition(672 / 2.0f, 768);

	Renderer* renderer = new Renderer("Level1Map");
	renderer->assignDrawable(mapSprite);
	attachComponent(renderer);
	
	// --- Define platform colliders ---
	std::vector<sf::FloatRect> platformBounds = {
		{0, 50, 100, 20},  // Example platform 1
		{200, 600, 300, 20},  // Example platform 2
		{350, 500, 250, 20},  // Example platform 3
	};

	std::vector<sf::RectangleShape*> boundingBoxes;

	for (const auto& bounds : platformBounds) {
		Collider* platformCollider = new Collider("platform");
		platformCollider->setLocalBounds(bounds);
		platformCollider->setCollisionListener(this);
		attachComponent(platformCollider);
		PhysicsManager::getInstance()->trackObject(platformCollider);

		/* Debug Lines for the bounding boxes */
		sf::RectangleShape* boundingBox = new sf::RectangleShape();
		boundingBox->setPosition(bounds.left, bounds.top);
		boundingBox->setSize(sf::Vector2f(bounds.width, bounds.height));
		boundingBox->setFillColor(sf::Color::Green);
		boundingBox->setOutlineColor(sf::Color::Green);
		boundingBox->setOutlineThickness(10);

		boundingBoxes.push_back(boundingBox);
	}


	// Attach each bounding box to a Renderer
	for (auto* box : boundingBoxes) {
		Renderer* boundingRenderer = new Renderer("PlatformBounds");
		boundingRenderer->assignDrawable(box);
		this->attachComponent(boundingRenderer);
	}
}

void Level1Map::onCollisionEnter(AGameObject* object)
{
	std::cout << "Collision detected with " << object->getName() << std::endl;
}

void Level1Map::onCollisionExit(AGameObject* object)
{
	std::cout << "platform collide done" << std::endl;
}

