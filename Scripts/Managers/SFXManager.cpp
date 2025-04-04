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
    loadAudio("1", "Assets/SFX/EnemyGunfire.wav");
    loadAudio("2", "Assets/SFX/Explosion1.wav");
    loadAudio("3", "Assets/SFX/Explosion2.wav");
    loadAudio("4", "Assets/SFX/LaunchMissile.wav");
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


