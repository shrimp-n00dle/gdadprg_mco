#include "SFXManager.hpp"
#include <iostream>

SFXManager* SFXManager::sharedInstance = nullptr;

/**
 * Returns the singleton instance of SFXManager, creating it if it doesn't exist
 * @return Pointer to the SFXManager instance
 */
SFXManager* SFXManager::getInstance()
{
    if (sharedInstance == nullptr)
    {
        sharedInstance = new SFXManager();
    }
    return sharedInstance;
}

/**
 * Constructor for SFXManager
 * Initializes background music and sets playing state to false
 */
SFXManager::SFXManager()
{
    bgMusic = new sf::Music();
    bBGMPlaying = false;
}

/**
 * Destructor for SFXManager
 * Cleans up all sound buffers, playlists, and background music
 */
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

    // Clean up BGM
    delete bgMusic;
}

/**
 * Loads all default audio files into the manager
 * Includes hammer, hit, intro, jumping, walking, victory sounds and background music
 */
void SFXManager::loadAll()
{
    loadAudio(AudioKeys::HAMMER, "Assets/SFX/hammer.wav");
    loadAudio(AudioKeys::HIT, "Assets/SFX/hit.wav");
    loadAudio(AudioKeys::INTRO, "Assets/SFX/intro.wav");
    loadAudio(AudioKeys::JUMPING, "Assets/SFX/jumping.wav");
    loadAudio(AudioKeys::WALKING, "Assets/SFX/walking.wav");
    loadAudio(AudioKeys::VICTORY, "Assets/SFX/victory.wav");
    loadBGM("Assets/SFX/25m.wav");
}

/**
 * Loads a single audio file into the manager
 * @param key Unique identifier for the audio
 * @param path File path to the audio file
 * @return true if audio was loaded successfully, false otherwise
 */
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

/**
 * Unloads an audio file from the manager
 * @param key Unique identifier of the audio to unload
 * @return true if audio was unloaded successfully
 */
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

/**
 * Checks if an audio file is currently loaded
 * @param key Unique identifier of the audio to check
 * @return true if audio is loaded, false otherwise
 */
bool SFXManager::isAudioLoaded(const std::string& key) const
{
    return AudioMap.find(key) != AudioMap.end();
}

/**
 * Gets the sound buffer for a specific audio key
 * @param key Unique identifier of the audio
 * @return Pointer to the sound buffer, or nullptr if not found
 */
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

/**
 * Gets the playlist for a specific audio key
 * @param key Unique identifier of the audio
 * @return Pointer to the playlist, or nullptr if not found
 */
Playlist* SFXManager::getPlaylist(const std::string& key)
{
    auto it = PlaylistMap.find(key);
    if (it != PlaylistMap.end())
    {
        return it->second;
    }
    return nullptr;
}

/**
 * Plays a sound effect
 * @param key Unique identifier of the sound to play
 */
void SFXManager::playSound(const std::string& key)
{
    Playlist* playlist = getPlaylist(key);
    if (playlist)
    {
        playlist->playSong();
    }
}

/**
 * Stops a sound effect
 * @param key Unique identifier of the sound to stop
 */
void SFXManager::stopSound(const std::string& key)
{
    Playlist* playlist = getPlaylist(key);
    if (playlist)
    {
        playlist->stopSong();
    }
}

/**
 * Pauses a sound effect
 * @param key Unique identifier of the sound to pause
 */
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

/**
 * Checks if a sound is currently playing
 * @param key Unique identifier of the sound to check
 * @return true if sound is playing, false otherwise
 */
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

/**
 * Sets the volume for all sounds (UNUSED)
 * @param volume Volume level (0-100)
 */
void SFXManager::setVolume(float volume)
{
    for (auto& pair : PlaylistMap)
    {
        sf::Sound* sound = pair.second->getSong();
        sound->setVolume(volume);
    }
}

/**
 * Sets the pitch for a specific sound (UNUSED)
 * @param key Unique identifier of the sound
 * @param pitch Pitch value to set
 */
void SFXManager::setPitch(const std::string& key, float pitch)
{
    Playlist* playlist = getPlaylist(key);
    if (playlist)
    {
        sf::Sound* sound = playlist->getSong();
        sound->setPitch(pitch);
    }
}

/**
 * Sets the loop state for a specific sound
 * @param key Unique identifier of the sound
 * @param loop true to loop the sound, false to play once
 */
void SFXManager::setLoop(const std::string& key, bool loop)
{
    Playlist* playlist = getPlaylist(key);
    if (playlist)
    {
        sf::Sound* sound = playlist->getSong();
        sound->setLoop(loop);
    }
}

/**
 * Loads background music from a file
 * @param path File path to the background music
 * @return true if music was loaded successfully, false otherwise
 */
bool SFXManager::loadBGM(const std::string& path)
{
    if (!bgMusic->openFromFile(path))
    {
        std::cout << "Failed to load BGM file: " << path << std::endl;
        return false;
    }
    return true;
}

/**
 * Plays the background music
 */
void SFXManager::playBGM()
{
    if (bgMusic->getStatus() != sf::Music::Playing || !bBGMPlaying)
    {
        bgMusic->play();
        bBGMPlaying = true;
    }
}

/**
 * Stops the background music
 */
void SFXManager::stopBGM()
{
    bgMusic->stop();
    bBGMPlaying = false;
}

/**
 * Pauses the background music
 */
void SFXManager::pauseBGM()
{
    if (bgMusic->getStatus() == sf::Music::Playing)
    {
        bgMusic->pause();
        bBGMPlaying = false;
    }
}

/**
 * Checks if background music is currently playing
 * @return true if background music is playing, false otherwise
 */
bool SFXManager::isBGMPlaying() const
{
    return bBGMPlaying;
}

/**
 * Sets the loop state for background music
 * @param loop true to loop the music, false to play once
 */
void SFXManager::setBGMLoop(bool loop)
{
    bgMusic->setLoop(loop);
}

/**
 * Sets the volume for background music
 * @param volume Volume level (0-100)
 */
void SFXManager::setBGMVolume(float volume)
{
    bgMusic->setVolume(volume);
}

/**
 * Sets the playing offset for background music (UNUSED)
 * @param seconds Time offset in seconds
 */
void SFXManager::setBGMOffset(float seconds)
{
    bgMusic->setPlayingOffset(sf::seconds(seconds));
}


