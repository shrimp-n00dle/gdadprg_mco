#include "TextureManager.hpp"
#include "iostream"

TextureManager* TextureManager::sharedInstance = nullptr;

TextureManager* TextureManager::getInstance()
{
    if (sharedInstance == nullptr)
    {
        sharedInstance = new TextureManager();
    }
    return sharedInstance;
}

void TextureManager::testFunction()
{
    std::cout << "TEST WORKS";
}

void TextureManager::loadAll()
{

    // BED, BENCH, COIN, GIFT, POOL Assets
    /*
   for (int i = 0; i < 8; i++)
   {
       std::string str_i = std::to_string(i);
       loadTexture("bed_" + str_i, "Assets/Bed/bed000" + str_i + ".png");
       loadTexture("bench_" + str_i, "Assets/Bench/bench000" + str_i + ".png");
       loadTexture("gift_" + str_i, "Assets/Gift/boxGift_000" + str_i + ".png");
       loadTexture("coin_" + str_i, "Assets/Coin/coin000" + str_i + ".png");
   }
   */
    // "Assets/Bed/bed0000.png"
    storeTexture("player", "Assets/MCOAssets/beam.png");
    storeTexture("ladder", "Assets/MCOAssets/ladder.png");
    storeTexture("hammer", "Assets/MCOAssets/hammer.jpg");

    /*OBJECTS*/
    storeTexture("avenger", "Assets/Objects/Avenger.png");

    loadTexture("desert_bg", "Assets/Objects/Desert.png");
    sf::Texture* bgTex;
    bgTex = getTexture("desert_bg");
    bgTex->setRepeated(true);

    storeTexture("eagle", "Assets/Objects/Eagle.png");
    storeTexture("raptor", "Assets/Objects/Raptor.png");
    storeTexture("spike", "Assets/Objects/spike.png");

    /*POOLABLES*/
    storeTexture("bullet", "Assets/Pool/bullet.png");

    /*UI*/
    storeTexture("btn_normal", "Assets/UI/b_4.png");
    storeTexture("btn_pressed", "Assets/UI/b_5.png");
    storeTexture("title_bg", "Assets/UI/f.png");
    storeTexture("menu_bar", "Assets/UI/bar_1.png");
    storeTexture("menu_bg", "Assets/UI/TitleScreenBG.png");

    /*SPRITE FRAMES*/
    storeTexture("sprite_sheet", "Assets/SpriteSheets/Dota_Sheet.png");
    storeTexture("walk_sheet", "Assets/MCOAssets/SpriteSheet/Walk/Walk.png");
    storeTexture("climb_sheet", "Assets/MCOAssets/SpriteSheet/Climb/Climb.png");

    storeTexture("level1", "Assets/Maps/25m.png");
   
}

void TextureManager::storeTexture(std::string name, std::string path)
{
    loadTexture(name, path);
    sf::Texture* assetTex;
    assetTex = getTexture(name);

}

void TextureManager::loadTexture(std::string key, std::string path)
{
    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile(path);
    textureMap[key] = texture;

    // NEVER DO THIS >> &mEnemyList[0]
}

sf::Texture* TextureManager::getTexture(std::string key)
{
    if (textureMap[key] != nullptr)
    {
        //std::cout << key << " found" << std::endl;
        return textureMap[key];
    } 
    
    else
    {
        std::cout << "No texture found for " << key << std::endl;
        return nullptr;
    }
}