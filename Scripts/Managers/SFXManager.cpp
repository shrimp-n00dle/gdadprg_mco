#include "SFXManager.hpp"
#include "iostream"

SFXManager* SFXManager::sharedInstance = NULL;

SFXManager* SFXManager::getInstance()
{
    if (sharedInstance == NULL)
    {
        sharedInstance = new SFXManager();
    }
    return sharedInstance;
}

void SFXManager::loadAll()
{
    //0
    loadAudio("hammer_sfx", "Assets/SFX/hammer.wav");

    //1
    loadAudio("hit_sfx", "Assets/SFX/hit.wav");

    //2
    loadAudio("intro_sfx", "Assets/SFX/intro.wav");
    
    //3
    loadAudio("jumping_sfx", "Assets/SFX/jumping.wav");

    //4
    loadAudio("walking_sfx", "Assets/SFX/walking.wav");
}

void SFXManager::loadAudio(std::string key, std::string path)
{
    sf::SoundBuffer* audio = new sf::SoundBuffer();
    audio->loadFromFile(path);
    AudioMap[key] = audio;

    /*prepare the song for the scene*/
    Playlist* newAudio = Playlist::readySongtoScene(AudioMap[key]);

    /*store the song in the audiolist*/
    mAudioList.push_back(newAudio);

    // NEVER DO THIS >> &mEnemyList[0]
}

sf::SoundBuffer* SFXManager::getAudio(std::string key)
{
    if (AudioMap[key] != nullptr)
    {
        return AudioMap[key];
    } 
    
    else
    {
        std::cout << "No audio found for " << key << std::endl;
        return nullptr;
    }
}


