#pragma once
#include "../GameObjects/Playlist.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "unordered_map"
#include <string>

// Audio key constants
namespace AudioKeys {
    const std::string HAMMER = "hammer_sfx";
    const std::string HIT = "hit_sfx";
    const std::string INTRO = "intro_sfx";
    const std::string JUMPING = "jumping_sfx";
    const std::string WALKING = "walking_sfx";
    const std::string VICTORY = "victory";
}

/*All audio clippings from https://www.youtube.com/watch?v=GKYUNtGrShc 
https://www.youtube.com/watch?v=KJkcNP4VkiM
*/
class SFXManager
{
public:
    static SFXManager* getInstance();
    ~SFXManager();

    // Core functionality
    void loadAll();
    bool loadAudio(const std::string& key, const std::string& path);
    sf::SoundBuffer* getAudio(const std::string& key);
    bool unloadAudio(const std::string& key);
    bool isAudioLoaded(const std::string& key) const;

    // Playlist management
    Playlist* getPlaylist(const std::string& key);
    void playSound(const std::string& key);
    void stopSound(const std::string& key);
    void pauseSound(const std::string& key);
    bool isSoundPlaying(const std::string& key) const;

    // Audio control
    void setVolume(float volume);
    void setPitch(const std::string& key, float pitch);
    void setLoop(const std::string& key, bool loop);

private:
    SFXManager();
    SFXManager(SFXManager const&) {};
    SFXManager& operator=(SFXManager const&){};
    static SFXManager* sharedInstance;

    // Audio dictionary holding all the sounds of the game
    std::unordered_map<std::string, sf::SoundBuffer*> AudioMap;
    std::unordered_map<std::string, Playlist*> PlaylistMap;
};