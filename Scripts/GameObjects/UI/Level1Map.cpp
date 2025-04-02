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
		// Bottom-left platform, every succeeding value goes upward
		{0, 744, 336, 16}, {336, 741, 48, 16}, {384, 738, 48, 16}, {432, 735, 48, 16},
		{480, 732, 48, 16}, {528, 729, 48, 16}, {576, 726, 48, 16}, {624, 723, 48, 16},
		
		// 2nd-floor platforms, every succeeding value goes upward
		{576, 660, 48, 16},	{528, 657, 48, 16}, {480, 654, 48, 16}, {432, 651, 48, 16},
		{384, 648, 48, 16}, {336, 645, 48, 16}, {288, 642, 48, 16}, {240, 639, 48, 16}, 
		{192, 636, 48, 16}, {144, 633, 48, 16}, {96, 630, 48, 16}, {48, 627, 48, 16},
		{0, 624, 48, 16},

		// 3nd-floor platforms, every succeeding value goes upward
		{48, 560, 48, 16}, {96, 557, 48, 16}, {144, 554, 48, 16}, {192, 551, 48, 16},
		{240, 548, 48, 16}, {288, 545, 48, 16}, {336, 542, 48, 16}, {384, 539, 48, 16},
		{432, 536, 48, 16}, {480, 533, 48, 16}, {528, 530, 48, 16}, {576, 527, 48, 16},
		{624, 524, 48, 16},

		// 4th-floor platforms, every succeeding value goes upward
		{576, 461, 48, 16}, {528, 458, 48, 16}, {480, 455, 48, 16}, {432, 452, 48, 16},
		{384, 449, 48, 16}, {336, 446, 48, 16}, {288, 443, 48, 16}, {240, 440, 48, 16},
		{192, 437, 48, 16}, {144, 434, 48, 16}, {96, 431, 48, 16}, {48, 428, 48, 16},
		{0, 425, 48, 16},

		// 5th-floor platforms, every succeeding value goes upward
		{48, 363, 48, 16}, {96, 360, 48, 16}, {144, 357, 48, 16}, {192, 354, 48, 16},
		{240, 351, 48, 16}, {288, 348, 48, 16}, {336, 345, 48, 16}, {384, 342, 48, 16},
		{432, 339, 48, 16}, {480, 336, 48, 16}, {528, 333, 48, 16}, {576, 330, 48, 16},
		{624, 327, 48, 16},

		// 6th-floor platforms, every succeeding value goes upward
		{576, 264, 48, 16}, {528, 261, 48, 16}, {480, 258, 48, 16}, {432, 255, 48, 16},
		{0, 252, 432, 16},

		// Final Platform
		{264, 167, 144, 16}
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
		boundingBox->setOrigin(0, 0);
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

