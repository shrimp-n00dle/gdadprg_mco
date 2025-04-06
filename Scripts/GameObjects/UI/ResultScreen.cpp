#include "ResultScreen.hpp"

ResultScreen::ResultScreen(std::string name) : AGameObject(name), ButtonListener()
{
}

void ResultScreen::initialize()
{
    sf::Sprite* sprite = new sf::Sprite();
    sprite->setTexture(*TextureManager::getInstance()->getTexture("title_bg"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

    Renderer* renderer = new Renderer("ResultScreen");
    renderer->assignDrawable(sprite);
    attachComponent(renderer);

    float posX = Game::WINDOW_WIDTH / 2;
    float posY = Game::WINDOW_HEIGHT / 2;
    setChildPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 3);
    transformable.setScale(sf::Vector2f(0.7f, 0.7f));

    // Title
    UIText* titleText = new UIText("title_text");
    this->attachChild(titleText);
    titleText->setChildPosition(0, -100);
    titleText->setSize(40);
    titleText->setFont("oldnesfont");
    titleText->setColor(sf::Color::Yellow);
    titleText->setTextStyled("LEVEL COMPLETED!");

    // Score Display
    UIText* scoreLabel = new UIText("score_label");
    this->attachChild(scoreLabel);
    scoreLabel->setChildPosition(-100, -20);
    scoreLabel->setSize(25);
    scoreLabel->setFont("oldnesfont");
    scoreLabel->setColor(sf::Color::White);
    scoreLabel->setTextStyled("SCORE:");

    scoreText = new UIText("score_value");
    this->attachChild(scoreText);
    scoreText->setChildPosition(100, -20);
    scoreText->setSize(25);
    scoreText->setFont("oldnesfont");
    scoreText->setColor(sf::Color::White);
    scoreText->setTextStyled("000000");

    // Bonus Display
    UIText* bonusLabel = new UIText("bonus_label");
    this->attachChild(bonusLabel);
    bonusLabel->setChildPosition(-100, 20);
    bonusLabel->setSize(25);
    bonusLabel->setFont("oldnesfont");
    bonusLabel->setColor(sf::Color::Cyan);
    bonusLabel->setTextStyled("BONUS:");

    bonusText = new UIText("bonus_value");
    this->attachChild(bonusText);
    bonusText->setChildPosition(100, 20);
    bonusText->setSize(25);
    bonusText->setFont("oldnesfont");
    bonusText->setColor(sf::Color::Cyan);
    bonusText->setTextStyled("0000");

    // Total Score Display
    UIText* totalLabel = new UIText("total_label");
    this->attachChild(totalLabel);
    totalLabel->setChildPosition(-100, 60);
    totalLabel->setSize(30);
    totalLabel->setFont("oldnesfont");
    totalLabel->setColor(sf::Color::Yellow);
    totalLabel->setTextStyled("TOTAL:");

    totalText = new UIText("total_value");
    this->attachChild(totalText);
    totalText->setChildPosition(100, 60);
    totalText->setSize(30);
    totalText->setFont("oldnesfont");
    totalText->setColor(sf::Color::Yellow);
    totalText->setTextStyled("000000");

    // Menu Button
    sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("blank_bg");
    sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("clicked_bg");
    UIButton* button = new UIButton("button_menu", btnNormal, btnPressed);
    this->attachChild(button);
    button->setChildPosition(0, 170);
    button->getTransformable()->setScale(0.3f, 0.3f);
    button->setButtonListener(this);

    UIText* button_Text = new UIText("text_menu");
    button->attachChild(button_Text);
    button_Text->setChildPosition(0, -20);
    button_Text->setSize(70);
    button_Text->setFont("oldnesfont");
    button_Text->setText("MAIN MENU");
}

void ResultScreen::setEnabled(bool flag)
{
    AGameObject::setEnabled(flag);
    if (flag) // Only update scores when screen becomes visible
    {
        updateScoreDisplay();
    }
}

void ResultScreen::updateScoreDisplay()
{
    // Format score with leading zeros
    std::stringstream scoreStream;
    scoreStream << std::setw(6) << std::setfill('0') << ScoreManager::getInstance()->getScore();
    scoreText->setTextStyled(scoreStream.str());

    std::stringstream bonusStream;
    bonusStream << std::setw(4) << std::setfill('0') << ScoreManager::getInstance()->getBonusScore();
    bonusText->setTextStyled(bonusStream.str());

    // Calculate and display total
    int totalScore = ScoreManager::getInstance()->getScore() + ScoreManager::getInstance()->getBonusScore();
    std::stringstream totalStream;
    totalStream << std::setw(6) << std::setfill('0') << totalScore;
    totalText->setTextStyled(totalStream.str());

    if (totalScore > ScoreManager::getInstance()->getHighScore())
    {
        // Since high score adding is already automatic via AddScore, let's just call that function.
        ScoreManager::getInstance()->addScore(0);
    }
}

void ResultScreen::onButtonClick(UIButton* button) {}

void ResultScreen::onButtonReleased(UIButton* button)
{
    if (button->getName() == "button_menu")
    {
        // Return to main menu
        SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);
    }
} 