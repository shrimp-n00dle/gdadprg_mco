#pragma once
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "unordered_map"

class SFXManager
{
public:
    static SFXManager* getInstance();

    void loadAll();
    sf::SoundBuffer* getAudio(std::string);

private:
    SFXManager() {};
    SFXManager(SFXManager const&) {};
    SFXManager& operator=(SFXManager const&){};
    static SFXManager* sharedInstance;

    void loadAudio(std::string,std::string);

    /*Audio dictionary holding all the songs of the game*/
    std::unordered_map<std::string,sf::SoundBuffer*> AudioMap;
};