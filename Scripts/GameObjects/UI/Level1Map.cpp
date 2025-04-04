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
		{0, 744, 336, 15}, {336, 741, 48, 15}, {384, 738, 48, 15}, {432, 735, 48, 15},
		{480, 732, 48, 15}, {528, 729, 48, 15}, {576, 726, 48, 15}, {624, 723, 48, 15},
		
		// 2nd-floor platforms, every succeeding value goes upward
		{576, 660, 48, 15},	{528, 657, 48, 15}, {480, 654, 48, 15}, {432, 651, 48, 15},
		{384, 648, 48, 15}, {336, 645, 48, 15}, {288, 642, 48, 15}, {240, 639, 48, 15}, 
		{192, 636, 48, 15}, {144, 633, 48, 15}, {96, 630, 48, 15}, {48, 627, 48, 15},
		{0, 624, 48, 15},

		// 3nd-floor platforms, every succeeding value goes upward
		{48, 560, 48, 15}, {96, 557, 48, 15}, {144, 554, 48, 15}, {192, 551, 48, 15},
		{240, 548, 48, 15}, {288, 545, 48, 15}, {336, 542, 48, 15}, {384, 539, 48, 15},
		{432, 536, 48, 15}, {480, 533, 48, 15}, {528, 530, 48, 15}, {576, 527, 48, 15},
		{624, 524, 48, 15},

		// 4th-floor platforms, every succeeding value goes upward
		{576, 461, 48, 15}, {528, 458, 48, 15}, {480, 455, 48, 15}, {432, 452, 48, 15},
		{384, 449, 48, 15}, {336, 446, 48, 15}, {288, 443, 48, 15}, {240, 440, 48, 15},
		{192, 437, 48, 15}, {144, 434, 48, 15}, {96, 431, 48, 15}, {48, 428, 48, 15},
		{0, 425, 48, 15},

		// 5th-floor platforms, every succeeding value goes upward
		{48, 363, 48, 15}, {96, 360, 48, 15}, {144, 357, 48, 15}, {192, 354, 48, 15},
		{240, 351, 48, 15}, {288, 348, 48, 15}, {336, 345, 48, 15}, {384, 342, 48, 15},
		{432, 339, 48, 15}, {480, 336, 48, 15}, {528, 333, 48, 15}, {576, 330, 48, 15},
		{624, 327, 48, 15},

		// 6th-floor platforms, every succeeding value goes upward
		{576, 264, 48, 15}, {528, 261, 48, 15}, {480, 258, 48, 15}, {432, 255, 48, 15},
		{0, 252, 432, 15},

		// Final Platform
		{264, 167, 144, 15}
	};

	std::vector<sf::RectangleShape*> boundingBoxes;

	for (int i = 0; i < platformBounds.size(); i++) {
		// Create unique name for each collider
		std::string colliderName = "PlatformCollider_" + std::to_string(i);

		Collider* platformCollider = new Collider(colliderName);
		platformCollider->setLocalBounds(platformBounds[i]);
		platformCollider->setCollisionListener(this);
		this->attachComponent(platformCollider);
		PhysicsManager::getInstance()->trackObject(platformCollider);

		/* Debug Lines for the bounding boxes */
		sf::RectangleShape* boundingBox = new sf::RectangleShape();
		boundingBox->setPosition(platformBounds[i].left, platformBounds[i].top);
		boundingBox->setOrigin(0, 0);
		boundingBox->setSize(sf::Vector2f(platformBounds[i].width, platformBounds[i].height));
		boundingBox->setFillColor(sf::Color(0, 255, 0, 100));  // Semi-transparent green
		boundingBox->setOutlineColor(sf::Color::Red);
		boundingBox->setOutlineThickness(2);

		boundingBoxes.push_back(boundingBox);
	}

	// Attach each bounding box to a Renderer
	/*
	for (auto* box : boundingBoxes) {
		Renderer* boundingRenderer = new Renderer("PlatformBounds");
		boundingRenderer->assignDrawable(box);
		this->attachComponent(boundingRenderer);
	}
	*/
}

void Level1Map::onCollisionEnter(AGameObject* object)
{
	std::cout << "Collision detected with " << object->getName() << std::endl;
}

void Level1Map::onCollisionExit(AGameObject* object)
{
	std::cout << "platform collide done" << std::endl;
}

