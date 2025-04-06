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
		{0, 744, 336, 7}, {336, 741, 48, 7}, {384, 738, 48, 7}, {432, 735, 48, 7},
		{480, 732, 48, 7}, {528, 729, 48, 7}, {576, 726, 48, 7}, {624, 723, 48, 7},
		
		// 2nd-floor platforms, every succeeding value goes upward
		{591, 660, 33, 7},	/*{528, 657, 5, 7},*/ {480, 654, 48, 7}, {432, 651, 48, 7},
		{384, 648, 48, 7}, {336, 645, 48, 7}, {288, 642, 48, 7}, {240, 639, 48, 7}, 
		{192, 636, 48, 7}, {144, 633, 48, 7}, {96, 630, 48, 7}, {48, 627, 48, 7},
		{0, 624, 48, 7},

		// 3rd-floor platforms, every succeeding value goes upward
		{48, 560, 48, 7}, {132, 557, 16, 7}, {144, 554, 48, 7}, {192, 551, 48, 7},
		{240, 548, 20, 7}, {320, 545, 16, 7}, {336, 542, 48, 7}, {384, 539, 48, 7},
		{432, 536, 48, 7}, {480, 533, 48, 7}, {528, 530, 48, 7}, {576, 527, 48, 7},
		{624, 524, 48, 7},

		// 4th-floor platforms, every succeeding value goes upward
		{600, 461, 24, 7}, {528, 458, 16, 7}, {480, 455, 48, 7}, {432, 452, 48, 7},
		{384, 449, 48, 7}, {368, 446, 16, 7}, {288, 443, 36, 7}, {240, 440, 48, 7},
		{192, 437, 48, 7}, {144, 434, 48, 7}, {96, 431, 48, 7}, {48, 428, 48, 7},
		{0, 425, 48, 7},

		// 5th-floor platforms, every succeeding value goes upward
		{48, 363, 36, 7}, {126, 360, 18, 7}, {144, 357, 48, 7}, {192, 354, 18, 7},
		{252, 351, 36, 7}, {288, 348, 48, 7}, {336, 345, 48, 7}, {384, 342, 48, 7},
		{432, 339, 48, 7}, {480, 336, 48, 7}, {528, 333, 48, 7}, {576, 330, 48, 7},
		{624, 327, 48, 7},

		// 6th-floor platforms, every succeeding value goes upward
		{588, 264, 36, 7}, {528, 261, 16, 7}, {480, 258, 48, 7}, {432, 255, 48, 7},
		{0, 252, 432, 7},

		// Final Platform
		{264, 167, 144, 7}
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

void Level1Map::onCollisionEnter(AGameObject* object) {}

void Level1Map::onCollisionExit(AGameObject* object) {}

