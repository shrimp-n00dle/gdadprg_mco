#include "Level1Map.hpp"

Level1Map::Level1Map(std::string name) : AGameObject(name)
{
	
}

void Level1Map::initialize()
{
	sf::Sprite* mapSprite = new sf::Sprite();
	mapSprite->setTexture(*TextureManager::getInstance()->getTexture("level1"));
	sf::Vector2u textureSize = mapSprite->getTexture()->getSize();
	std::cout << "Texture Size: " << textureSize.x << ", " << textureSize.y << std::endl;
	mapSprite->setOrigin(textureSize.x / 2.0f, textureSize.y);
	mapSprite->setScale(3.0f, 3.0f);
	mapSprite->setPosition(672 / 2.0f, 768);

	Renderer* renderer = new Renderer("Level1Map");
	renderer->assignDrawable(mapSprite);
	attachComponent(renderer);
	



	float mapScaleX = mapSprite->getScale().x;
	float mapScaleY = mapSprite->getScale().y;
	sf::Vector2f mapOrigin = sf::Vector2f(textureSize.x / 2.0f, textureSize.y);
	sf::Vector2f mapPos = sf::Vector2f(672 / 2.0f, 768);

	// --- Define platform colliders ---
	std::vector<sf::FloatRect> platformBounds = {
		{0, -20, 50, 50},	// Example platform 1
		{50, 50, 300, 20}		// Example platform 2
		//{100, 100, 250, 20},	// Example platform 3
	};

	std::vector<sf::RectangleShape*> boundingBoxes;

	for (const auto& bounds : platformBounds) {

		Collider* platformCollider = new Collider("PlatformCollider");
		platformCollider->setLocalBounds(bounds);
		platformCollider->setCollisionListener(this);
		this->attachComponent(platformCollider);
		PhysicsManager::getInstance()->trackObject(platformCollider);


		/* Debug Lines for the bounding boxes */
		sf::RectangleShape* boundingBox = new sf::RectangleShape();
		boundingBox->setPosition(bounds.left, bounds.top);
		boundingBox->setSize(sf::Vector2f(bounds.width, bounds.height));
		boundingBox->setFillColor(sf::Color(0, 255, 0, 100));  // Semi-transparent green
		boundingBox->setOutlineColor(sf::Color::Red);
		boundingBox->setOutlineThickness(2);

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

