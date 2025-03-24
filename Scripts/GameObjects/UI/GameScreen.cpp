#include "GameScreen.hpp"

GameScreen::GameScreen(std::string name) : AGameObject(name), ButtonListener()
{

}

void GameScreen::initialize()
{
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("desert_bg"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("GameScreen");
	renderer->assignDrawable(sprite);
	attachComponent(renderer);

	float posX = Game::WINDOW_WIDTH / 2;
	float posY = Game::WINDOW_HEIGHT / 2;
	setChildPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
	transformable.setScale(sf::Vector2f(0.7f, 0.7f));
}

void GameScreen::onButtonClick(UIButton* button) {}

void GameScreen::onButtonReleased(UIButton* button) {}


