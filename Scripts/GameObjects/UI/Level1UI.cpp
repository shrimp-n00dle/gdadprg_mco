#include "Level1UI.hpp"
#include <sstream>
#include <iomanip>

Level1UI::Level1UI(std::string name) : AGameObject(name), ButtonListener()
{
}

void Level1UI::initialize()
{
	// 1UP Text
	UIText* playerText = new UIText("1upText");
	this->attachChild(playerText);
	playerText->setChildPosition(110, 18);
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
	levelText->setTextStyled("L=00");

	// Bonus Score (top right)
	bonusText = new UIText("bonusText");
	this->attachChild(bonusText);
	bonusText->setChildPosition(590, 158);
	bonusText->setSize(18);
	bonusText->setColor(sf::Color::Cyan);
	bonusText->setTextStyled("5000");

	// Initial score update
	updateScoreDisplay();
}

void Level1UI::update(sf::Time deltaTime)
{
	updateScoreDisplay();
	updateBonusScore(deltaTime);
}

void Level1UI::updateScoreDisplay()
{
	std::stringstream scoreStream;
	scoreStream << std::setw(6) << std::setfill('0') << ScoreManager::getInstance()->getScore();
	playerScoreText->setTextStyled(scoreStream.str());

	// Format high score with leading zeros
	std::stringstream highScoreStream;
	highScoreStream << std::setw(6) << std::setfill('0') << ScoreManager::getInstance()->getHighScore();
	highScoreText->setTextStyled(highScoreStream.str());
}

void Level1UI::updateBonusScore(sf::Time deltaTime)
{
	bonusCountdown += deltaTime;
	if (bonusCountdown >= sf::seconds(1.0f))
	{
		bonusCountdown = sf::Time::Zero;
		bonusScore = std::max(0, bonusScore - 50); // Decrease by 50 every second
		std::stringstream bonusStream;
		bonusStream << std::setw(4) << std::setfill('0') << bonusScore;
		bonusText->setTextStyled(bonusStream.str());
	}
}

void Level1UI::onButtonClick(UIButton* button)
{
	if (button->getName() == "button_yes")
	{
		// ApplicationManager::getInstance()->applicationQuit();
	}
	else if (button->getName() == "button_no")
	{
		// this->setEnabled(false);
	}
}

void Level1UI::onButtonReleased(UIButton* button)
{
}
