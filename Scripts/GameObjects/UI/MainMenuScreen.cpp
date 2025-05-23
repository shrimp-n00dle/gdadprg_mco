#include "MainMenuScreen.hpp"

/**
 * Constructor for MainMenuScreen object
 * @param name Name identifier for the main menu screen
 */
MainMenuScreen::MainMenuScreen(std::string name) : AGameObject(name), ButtonListener()
{

}

/**
 * Initializes the main menu screen
 * Sets up the background, text elements, and navigation buttons
 */
void MainMenuScreen::initialize()
{
	ApplicationManager::getInstance()->resumeApplication();
	isIntroPlaying = false;
	introDelay = 0.0f;

	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("menu_bg"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("MainMenuScreen");
	renderer->assignDrawable(sprite);
	attachComponent(renderer);

	float posX = Game::WINDOW_WIDTH / 2;
	float posY = Game::WINDOW_HEIGHT / 2;
	setChildPosition(posX, posY / 2);
	transformable.setScale(sf::Vector2f(0.8f, 0.8f));

	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("blank_bg");

	UIButton* button1 = new UIButton("button_1", btnNormal, btnNormal);
	this->attachChild(button1);
	button1->setChildPosition(0,300);
	button1->getTransformable()->setScale(0.3f, 0.3f);
	button1->setButtonListener(this);

	UIText* button1_Text = new UIText("text_1");
	button1->attachChild(button1_Text);
	button1_Text->setChildPosition(0,-20);
	button1_Text->setColor(sf::Color(254, 161, 59));
	button1_Text->setSize(85);
	button1_Text->setText("PLAY DEMO");

	UIButton* button2 = new UIButton("button_2", btnNormal, btnNormal);
	this->attachChild(button2);
	button2->setChildPosition(0,400);
	button2->getTransformable()->setScale(0.3f, 0.3f);
	button2->setButtonListener(this);

	UIText* button2_Text = new UIText("text_2");
	button2->attachChild(button2_Text);
	button2_Text->setChildPosition(0,-20);
	button2_Text->setSize(85);
	button2_Text->setColor(sf::Color(254, 161, 59));
	button2_Text->setText("QUIT GAME");

	UIText* credits = new UIText("credits");
	this->attachChild(credits);
	credits->setChildPosition(0, 600);
	credits->setSize(25);
	credits->setFont("oldnesfont");
	credits->setText("2025, VINGNO & CAO");
}

/**
 * Called when a button is clicked
 * Handles menu navigation and game start
 * @param button The button that was clicked
 */
void MainMenuScreen::onButtonClick(UIButton* button)
{
	//START GAME
	if (button->getName() == "button_1")
	{
		// Play intro sound and start delay
		SFXManager::getInstance()->playSound(AudioKeys::INTRO);
		isIntroPlaying = true;
		introDelay = 0.0f;
	}

	//QUIT 
	else if (button->getName() == "button_2")
	{
		GameObjectManager::getInstance()->findObjectByName("QuitScreen")->setEnabled(true);
	}
}

/**
 * Called when a button is released
 * @param button The button that was released
 */
void MainMenuScreen::onButtonReleased(UIButton* button) {}

/**
 * Updates the main menu state
 * Handles intro sound delay and scene transition
 * @param deltaTime Time elapsed since last update
 */
void MainMenuScreen::update(sf::Time deltaTime)
{
	if (isIntroPlaying)
	{
		introDelay += deltaTime.asSeconds();
		
		// Wait for the intro sound to finish before changing scenes
		if (introDelay >= INTRO_SOUND_DURATION)
		{
			isIntroPlaying = false;
			SceneManager::getInstance()->loadScene(SceneManager::MCOGAME_SCENE_NAME);
			ApplicationManager::getInstance()->resumeApplication();
		}
	}
}

