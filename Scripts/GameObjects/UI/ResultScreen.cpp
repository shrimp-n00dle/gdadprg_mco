#include "ResultScreen.hpp"

ResultScreen::ResultScreen(std::string name) : AGameObject(name), ButtonListener()
{
}

void ResultScreen::initialize()
{
    ApplicationManager::getInstance()->pauseApplication();

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

    sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
    sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

    UIText* menu_Text = new UIText("result_text");
    this->attachChild(menu_Text);
    menu_Text->setChildPosition(0, -20);
    menu_Text->setSize(30);
    menu_Text->setTextStyled("LEVEL COMPLETED!");

    UIButton* button = new UIButton("button_menu", btnNormal, btnPressed);
    this->attachChild(button);
    button->setChildPosition(0, 150);
    button->getTransformable()->setScale(0.3f, 0.3f);
    button->setButtonListener(this);

    UIText* button_Text = new UIText("text_menu");
    button->attachChild(button_Text);
    button_Text->setChildPosition(0, -20);
    button_Text->setSize(100);
    button_Text->setText("MAIN MENU");
}

void ResultScreen::onButtonClick(UIButton* button)
{
    if (button->getName() == "button_menu")
    {
        // Return to main menu
        SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);
    }
}

void ResultScreen::onButtonReleased(UIButton* button) {} 