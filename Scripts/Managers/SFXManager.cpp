#include "SFXManager.hpp"
#include <iostream>

SFXManager* SFXManager::sharedInstance = nullptr;

SFXManager* SFXManager::getInstance()
{
    if (sharedInstance == nullptr)
    {
        sharedInstance = new SFXManager();
    }
    return sharedInstance;
}

SFXManager::SFXManager()
{
    // Initialize any default values here
}

SFXManager::~SFXManager()
{
    // Clean up all sound buffers
    for (auto& pair : AudioMap)
    {
        delete pair.second;
    }
    AudioMap.clear();

    // Clean up all playlists
    for (auto& pair : PlaylistMap)
    {
        delete pair.second;
    }
    PlaylistMap.clear();
}

void SFXManager::loadAll()
{
    loadAudio(AudioKeys::HAMMER, "Assets/SFX/hammer.wav");
    loadAudio(AudioKeys::HIT, "Assets/SFX/hit.wav");
    loadAudio(AudioKeys::INTRO, "Assets/SFX/intro.wav");
    loadAudio(AudioKeys::JUMPING, "Assets/SFX/jumping.wav");
    loadAudio(AudioKeys::WALKING, "Assets/SFX/walking.wav");
    loadAudio(AudioKeys::VICTORY, "Assets/SFX/victory.wav");
}

bool SFXManager::loadAudio(const std::string& key, const std::string& path)
{
    // Check if audio is already loaded
    if (AudioMap.find(key) != AudioMap.end())
    {
        std::cout << "Audio with key '" << key << "' is already loaded." << std::endl;
        return false;
    }

    // Create and load the sound buffer
    sf::SoundBuffer* audio = new sf::SoundBuffer();
    if (!audio->loadFromFile(path))
    {
        std::cout << "Failed to load audio file: " << path << std::endl;
        delete audio;
        return false;
    }

    // Store the sound buffer
    AudioMap[key] = audio;

    // Create and store the playlist
    Playlist* newAudio = Playlist::readySongtoScene(audio);
    PlaylistMap[key] = newAudio;

    return true;
}

bool SFXManager::unloadAudio(const std::string& key)
{
    auto audioIt = AudioMap.find(key);
    auto playlistIt = PlaylistMap.find(key);

    if (audioIt != AudioMap.end())
    {
        delete audioIt->second;
        AudioMap.erase(audioIt);
    }

    if (playlistIt != PlaylistMap.end())
    {
        delete playlistIt->second;
        PlaylistMap.erase(playlistIt);
    }

    return true;
}

bool SFXManager::isAudioLoaded(const std::string& key) const
{
    return AudioMap.find(key) != AudioMap.end();
}

sf::SoundBuffer* SFXManager::getAudio(const std::string& key)
{
    auto it = AudioMap.find(key);
    if (it != AudioMap.end())
    {
        return it->second;
    }
    
    std::cout << "No audio found for key: " << key << std::endl;
    return nullptr;
}

Playlist* SFXManager::getPlaylist(const std::string& key)
{
    auto it = PlaylistMap.find(key);
    if (it != PlaylistMap.end())
    {
        return it->second;
    }
    return nullptr;
}

void SFXManager::playSound(const std::string& key)
{
    Playlist* playlist = getPlaylist(key);
    if (playlist)
    {
        playlist->playSong();
    }
}

void SFXManager::stopSound(const std::string& key)
{
    Playlist* playlist = getPlaylist(key);
    if (playlist)
    {
        playlist->stopSong();
    }
}

void SFXManager::pauseSound(const std::string& key)
{
    Playlist* playlist = getPlaylist(key);
    if (playlist)
    {
        sf::Sound* sound = playlist->getSong();
        if (sound->getStatus() == sf::Sound::Playing)
        {
            sound->pause();
        }
    }
}

bool SFXManager::isSoundPlaying(const std::string& key) const
{
    auto it = PlaylistMap.find(key);
    if (it != PlaylistMap.end())
    {
        sf::Sound* sound = it->second->getSong();
        return sound->getStatus() == sf::Sound::Playing;
    }
    return false;
}

void SFXManager::setVolume(float volume)
{
    for (auto& pair : PlaylistMap)
    {
        sf::Sound* sound = pair.second->getSong();
        sound->setVolume(volume);
    }
}

void SFXManager::setPitch(const std::string& key, float pitch)
{
    Playlist* playlist = getPlaylist(key);
    if (playlist)
    {
        sf::Sound* sound = playlist->getSong();
        sound->setPitch(pitch);
    }
}

void SFXManager::setLoop(const std::string& key, bool loop)
{
    Playlist* playlist = getPlaylist(key);
    if (playlist)
    {
        sf::Sound* sound = playlist->getSong();
        sound->setLoop(loop);
    }
}


