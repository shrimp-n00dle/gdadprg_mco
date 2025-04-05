#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Components/AComponent.hpp"
#include "Components/AirplaneSupportMovement.hpp"
#include "Components/BGMovement.hpp"
#include "Components/Collider.hpp"
#include "Components/EnemyBehaviour.hpp"
#include "Components/EnemySwarmHandler.hpp"
#include "Components/MCOPlayerMovement.hpp"
#include "Components/PlayerMovement.hpp"
#include "Components/ProjectileMovement.hpp"

#include "GameObjects/Listeners/ButtonListener.hpp"
#include "GameObjects/Listeners/CollisionListener.hpp"

#include "GameObjects/Poolables/EnemyAirplane.hpp"
#include "GameObjects/Poolables/GameObjectPool.hpp"
#include "GameObjects/Poolables/ProjectileObject.hpp"

#include "GameObjects/Scenes/AScene.hpp"
#include "GameObjects/Scenes/GameScene.hpp"
#include "GameObjects/Scenes/JScene.hpp"
#include "GameObjects/Scenes/MainMenuScene.hpp"
#include "GameObjects/Scenes/SpriteScene.hpp"

#include "GameObjects/UI/GameScreen.hpp"
#include "GameObjects/UI/MainMenuScreen.hpp"
#include "GameObjects/UI/MenuBar.hpp"
#include "GameObjects/UI/Level1Map.hpp"
#include "GameObjects/UI/Level1UI.hpp"
#include "GameObjects/UI/QuitScreen.hpp"
#include "GameObjects/UI/ReturnScreen.hpp"
#include "GameObjects/UI/UIButton.hpp"
#include "GameObjects/UI/UIText.hpp"

#include "GameObjects/AGameObject.hpp"
#include "GameObjects/AirplanePlayer.hpp"
#include "GameObjects/AirplaneSupport.hpp"
#include "GameObjects/APoolable.hpp"
#include "GameObjects/BGameObject.hpp"
#include "GameObjects/EGameObject.hpp"
#include "GameObjects/Entity.hpp"
#include "GameObjects/Player.hpp"
#include "GameObjects/Playlist.hpp"
#include "GameObjects/Text.hpp"

#include "Inputs/BGInput.hpp"
#include "Inputs/GenericInput.hpp"
#include "Inputs/PlayerInput.hpp"
#include "Inputs/UIButtonInput.hpp"

#include "Managers/ApplicationManager.hpp"
#include "Managers/FontManager.hpp"
#include "Managers/GameObjectManager.hpp"
#include "Managers/ObjectPoolHolder.hpp"
#include "Managers/PhysicsManager.hpp"
#include "Managers/SceneManager.hpp"
#include "Managers/SFXManager.hpp"
#include "Managers/TextureManager.hpp"

#include "Renderer/Renderer.hpp"

class Game {
public:
    Game();
    void run();
    float PlayerSpeed = 300.0f;
    bool bPlaying = false;

    /*For ship's rotation*/
    float rawValue = 0.0f;

    const sf::Time TimePerFrame = sf::seconds(1.f/60.0f);

    //640
    static const int WINDOW_WIDTH = 672;

    //480
    static const int WINDOW_HEIGHT = 768;

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handleMouseInput(sf::Mouse::Button button, bool isPressed);

    void handleAudioInput(sf::Keyboard::Key key, bool isPressed);

    void addEntity(std::string key, float x, float y);

private:
    sf::RenderWindow mWindow;
    Entity mSampleEntity;
    float debugTimer = 0;


    std::vector<Entity*> mEntityList;
 

    bool mIsMovingUp = false;
    bool mIsMovingDown = false;
    bool mIsMovingLeft = false;
    bool mIsMovingRight = false;

    bool bMouseClicked = false;

    bool bAudio1 = false; 
    bool bAudio2 = false;
    bool bAudio3 = false;
    bool bAudio4 = false;

};
