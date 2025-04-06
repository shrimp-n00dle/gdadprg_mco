#include "Level1UI.hpp"
#include <sstream>
#include <iomanip>

/**
 * Constructor for Level1UI object
 * @param name Name identifier for the level 1 UI
 */
Level1UI::Level1UI(std::string name) : AGameObject(name), ButtonListener()
{
}

/**
 * Initializes the level 1 UI
 * Sets up score displays, high score, level number, bonus score, and pause button
 */
void Level1UI::initialize()
{
	// 1UP Text
	UIText* playerText = new UIText("1upText");
	this->attachChild(playerText);
	playerText->setChildPosition(120, 18);
	playerText->setSize(20);
	playerText->setColor(sf::Color::Red);
	playerText->setTextStyled("1UP");

	// Player Score
	playerScoreText = new UIText("playerScore");
	this->attachChild(playerScoreText);
	playerScoreText->setChildPosition(110, 42);
	playerScoreText->setSize(20);
	playerScoreText->setColor(sf::Color::White);
	playerScoreText->setTextStyled("000000");

	// HIGH SCORE Text
	UIText* highScoreTextLabel = new UIText("highScoreText");
	this->attachChild(highScoreTextLabel);
	highScoreTextLabel->setChildPosition(345, 18);
	highScoreTextLabel->setSize(20);
	highScoreTextLabel->setColor(sf::Color::Red);
	highScoreTextLabel->setTextStyled("HIGH SCORE");

	// High Score Value
	highScoreText = new UIText("highScore");
	this->attachChild(highScoreText);
	highScoreText->setChildPosition(345, 42);
	highScoreText->setSize(20);
	highScoreText->setColor(sf::Color::White);
	highScoreText->setTextStyled("000000");

	// Level Number Text
	UIText* levelText = new UIText("levelText");
	this->attachChild(levelText);
	levelText->setChildPosition(550, 90);
	levelText->setFont("default");
	levelText->setSize(25);
	levelText->setColor(sf::Color(0, 0, 170));
	levelText->setTextStyled("L=01");

	// Bonus Score (top right)
	bonusText = new UIText("bonusText");
	this->attachChild(bonusText);
	bonusText->setChildPosition(590, 158);
	bonusText->setSize(18);
	bonusText->setColor(sf::Color::Cyan);
	bonusText->setTextStyled("5000");

	// Pause Button
	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_pause");
	UIButton* pauseButton = new UIButton("pause_button", btnNormal, btnNormal);
	this->attachChild(pauseButton);
	pauseButton->setChildPosition(620, 30);
	pauseButton->getTransformable()->setScale(0.13f, 0.13f);
	pauseButton->setButtonListener(this);

	// Initial score update
	updateScoreDisplay();
}

/**
 * Updates the level 1 UI state
 * Updates score display and bonus score countdown
 * @param deltaTime Time elapsed since last update
 */
void Level1UI::update(sf::Time deltaTime)
{
	updateScoreDisplay();
	updateBonusScore(deltaTime);
}

/**
 * Updates the score display with current values
 * Formats and displays player score and high score
 */
void Level1UI::updateScoreDisplay()
{
	std::stringstream scoreStream;
	scoreStream << std::setw(6) << std::setfill('0') << ScoreManager::getInstance()->getScore();
	playerScoreText->setTextStyled(scoreStream.str());

	std::stringstream highScoreStream;
	highScoreStream << std::setw(6) << std::setfill('0') << ScoreManager::getInstance()->getHighScore();
	highScoreText->setTextStyled(highScoreStream.str());
}

/**
 * Updates the bonus score countdown
 * Decreases bonus score over time and updates display
 * @param deltaTime Time elapsed since last update
 */
void Level1UI::updateBonusScore(sf::Time deltaTime)
{
	bonusCountdown += deltaTime;
	if (bonusCountdown >= sf::seconds(1.0f))
	{
		int currentBonus = ScoreManager::getInstance()->getBonusScore();
		currentBonus = std::max(0, currentBonus - 50); // Decrease by 50 every second
		ScoreManager::getInstance()->saveBonusScore(currentBonus);
		
		std::stringstream bonusStream;
		bonusStream << std::setw(4) << std::setfill('0') << currentBonus;
		bonusText->setTextStyled(bonusStream.str());
		
		bonusCountdown = sf::Time::Zero;
	}
}

/**
 * Called when a button is clicked
 * @param button The button that was clicked
 */
void Level1UI::onButtonClick(UIButton* button) {}

/**
 * Called when a button is released
 * Handles pause button functionality
 * @param button The button that was released
 */
void Level1UI::onButtonReleased(UIButton* button)
{
	if (button->getName() == "pause_button")
	{
		std::cout << "pause clicked" << std::endl;
		SFXManager::getInstance()->pauseBGM();
		PauseScreen* pauseScreen = (PauseScreen*)GameObjectManager::getInstance()->findObjectByName("PauseScreen");
		pauseScreen->setEnabled(true);
		ApplicationManager::getInstance()->pauseApplication();
	}
}
