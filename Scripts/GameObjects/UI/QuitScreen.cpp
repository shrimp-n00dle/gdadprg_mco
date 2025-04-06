#include "QuitScreen.hpp"

/**
 * Constructor for QuitScreen object
 * @param name Name identifier for the quit screen
 */
QuitScreen::QuitScreen(std::string name) : AGameObject(name), ButtonListener()
{

}

/**
 * Initializes the quit screen
 * Sets up the background, text elements, and confirmation buttons
 */
void QuitScreen::initialize()
{
	//std::cout << "Declared as " << this->getName() << std::endl;
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("title_bg"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("QuitScreen");
	renderer->assignDrawable(sprite);
	attachComponent(renderer);

	float posX = Game::WINDOW_WIDTH / 2;
	float posY = Game::WINDOW_HEIGHT / 2;
	setChildPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 3);
	transformable.setScale(sf::Vector2f(0.7f, 0.7f));

	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("blank_bg");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("clicked_bg");

	UIText* menu_Text = new UIText("inquiry_text");
	this->attachChild(menu_Text);
	menu_Text->setChildPosition(0, -20);
	menu_Text->setSize(30);
	menu_Text->setFont("oldnesfont");
	menu_Text->setTextStyled("ARE YOU SURE YOU WANT TO QUIT THE GAME?");

	UIButton* button1 = new UIButton("button_yes", btnNormal, btnPressed);
	this->attachChild(button1);
	button1->setChildPosition(-130, 150);
	button1->getTransformable()->setScale(0.3f, 0.3f);
	button1->setButtonListener(this);

	UIText* button1_Text = new UIText("text_yes");
	button1->attachChild(button1_Text);
	button1_Text->setChildPosition(0, -20);
	button1_Text->setSize(100);
	button1_Text->setText("YES");

	UIButton* button2 = new UIButton("button_no", btnNormal, btnPressed);
	this->attachChild(button2);
	button2->setChildPosition(130,150);
	button2->getTransformable()->setScale(0.3f, 0.3f);
	button2->setButtonListener(this);

	UIText* button2_Text = new UIText("text_no");
	button2->attachChild(button2_Text);
	button2_Text->setChildPosition(0, -20);
	button2_Text->setSize(100);
	button2_Text->setText("NO");
}

/**
 * Called when a button is clicked
 * Handles quit confirmation
 * @param button The button that was clicked
 */
void QuitScreen::onButtonClick(UIButton* button)
{
	if (button->getName() == "button_yes")
	{
		ApplicationManager::getInstance()->applicationQuit();
	}
	else if (button->getName() == "button_no")
	{
		this->setEnabled(false);
	}
}

/**
 * Called when a button is released
 * @param button The button that was released
 */
void QuitScreen::onButtonReleased(UIButton* button) {}

