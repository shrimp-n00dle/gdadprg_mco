#include "MenuBar.hpp"

MenuBar::MenuBar(std::string name) : AGameObject(name), ButtonListener()
{

}

void MenuBar::initialize()
{
	//std::cout << "Declared as " << this->getName() << std::endl;
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("menu_bar"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("MenuBar");
	renderer->assignDrawable(sprite);
	attachComponent(renderer);

	float posX = Game::WINDOW_WIDTH / 2;
	float posY = Game::WINDOW_HEIGHT / 2;
	setChildPosition(Game::WINDOW_WIDTH - 175, Game::WINDOW_HEIGHT - 30);
	transformable.setScale(sf::Vector2f(0.7,0.7));

	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

	UIButton* button1 = new UIButton("menu_button", btnNormal, btnPressed);
	this->attachChild(button1);
	button1->setChildPosition(150,0);
	button1->getTransformable()->setScale(0.2f, 0.2f);
	button1->setButtonListener(this);

	UIText* button1_Text = new UIText("text_1");
	button1->attachChild(button1_Text);
	button1_Text->setChildPosition(0, -20);
	button1_Text->setSize(100);
	button1_Text->setText("QUIT");
}

void MenuBar::onButtonClick(UIButton* button)
{
	ApplicationManager::getInstance()->pauseApplication();
	GameObjectManager::getInstance()->findObjectByName("ReturnScreen")->setEnabled(true);
}

void MenuBar::onButtonReleased(UIButton* button) {}

