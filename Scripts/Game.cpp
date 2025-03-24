#include "Game.hpp"
#include "iostream"
#include "cmath"
#include "string"

#define PI 3.14159



Game::Game() : mWindow(sf::VideoMode(300, 300), "Jan Vingno")
{
    /*Framerate is set to 60*/
    mWindow.setFramerateLimit(60);

    
    TextureManager::getInstance()->loadAll();
    FontManager::getInstance()->loadAll();
    //SFXManager::getInstance()->loadAll();

    //register scenes
    //SceneManager::getInstance()->registerScene(new MainMenuScene());
    //SceneManager::getInstance()->registerScene(new GameScene());
    SceneManager::getInstance()->registerScene(new SpriteScene());

    //load first scene
    //SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);
    //SceneManager::getInstance()->loadScene(SceneManager::GAME_SCENE_NAME);
    SceneManager::getInstance()->loadScene(SceneManager::SPRITE_SCENE_NAME);
}

void Game::run()
{
    sf::Clock clock;

    /*to avoid lagging and help with collision detection*/
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    /*Game Loop*/
    while (mWindow.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
        SceneManager::getInstance()->checkLoadScene();
    }
}

void Game::processEvents()
{
    sf::Event event;
        while (mWindow.pollEvent(event))
        {
        switch(event.type)
        {
            case sf::Event::Closed:

                mWindow.close();
                break;

            default:
                GameObjectManager::getInstance()->processInput(event);
                break;
           
        }
        }
}

void Game::update(sf::Time deltaTime)
{
  

    if (!ApplicationManager::getInstance()->isPaused())
    {
        GameObjectManager::getInstance()->update(deltaTime);
    }
}

void Game::render()
{
    mWindow.clear();

    GameObjectManager::getInstance()->draw(&mWindow);
    
    mWindow.display();
}


void Game::handleAudioInput(sf::Keyboard::Key key, bool isPressed)
{
    switch(key)
    {
        case sf::Keyboard::Num1:
        bAudio1 = isPressed;
        break;

        case sf::Keyboard::Num2:
        bAudio2 = isPressed;
        break;

        case sf::Keyboard::Num3:
        bAudio3 = isPressed;
        break;

        case sf::Keyboard::Num4:
        bAudio4 = isPressed;
        break;
    }
}

void Game::handleMouseInput(sf::Mouse::Button button, bool isPressed)
{
    switch(button)
    {
        case sf::Mouse::Left:
        bMouseClicked = isPressed;
        break;
    }
}

void Game::addEntity(std::string key, float x, float y)
{
    sf::Texture* texture = TextureManager::getInstance()->getTexture(key);
    Entity* newEntity = Entity::createEntity(texture,x,y);
    mEntityList.push_back(newEntity);
}

void Game::addAudio(std::string key)
{
    /*get the audio from the main library*/
    sf::SoundBuffer* audio = SFXManager::getInstance()->getAudio(key);

    /*prepare the song for the scene*/
    Playlist* newAudio = Playlist::readySongtoScene(audio);

    /*store the song in the audiolist*/
    mAudioList.push_back(newAudio);
}
