#include "MainMenuScreen.hpp"

MainMenuScreen::MainMenuScreen(std::string name) : AGameObject(name), ButtonListener()
{

}

void MainMenuScreen::initialize()
{
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("menu_bg"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("MainMenuScreen");
	renderer->assignDrawable(sprite);
	attachComponent(renderer);

	float posX = Game::WINDOW_WIDTH / 2;
	float posY = Game::WINDOW_HEIGHT / 2;
	setChildPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
	transformable.setScale(sf::Vector2f(0.7f, 0.7f));

	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

	UIButton* button1 = new UIButton("button_1", btnNormal, btnPressed);
	this->attachChild(button1);
	button1->setChildPosition(0,-50);
	button1->getTransformable()->setScale(0.3f, 0.3f);
	button1->setButtonListener(this);


	UIText* button1_Text = new UIText("text_1");
	button1->attachChild(button1_Text);
	button1_Text->setChildPosition(0,-20);
	button1_Text->setSize(85);
	button1_Text->setText("PLAY GAME");

	UIButton* button2 = new UIButton("button_2", btnNormal, btnPressed);
	this->attachChild(button2);
	button2->setChildPosition(0,50);
	button2->getTransformable()->setScale(0.3f, 0.3f);
	button2->setButtonListener(this);

	UIText* button2_Text = new UIText("text_2");
	button2->attachChild(button2_Text);
	button2_Text->setChildPosition(0,-20);
	button2_Text->setSize(85);
	button2_Text->setText("QUIT");
}

void MainMenuScreen::onButtonClick(UIButton* button)
{
	//START GAME
	if (button->getName() == "button_1")
	{
		
		SceneManager::getInstance()->loadScene(SceneManager::MCOGAME_SCENE_NAME);
		ApplicationManager::getInstance()->resumeApplication();
	}

	//QUIT 
	else if (button->getName() == "button_2")
	{
		GameObjectManager::getInstance()->findObjectByName("QuitScreen")->setEnabled(true);
	}
}

void MainMenuScreen::onButtonReleased(UIButton* button) {}

