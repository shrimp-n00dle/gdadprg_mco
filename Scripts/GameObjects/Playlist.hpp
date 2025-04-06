#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

/*A gameobject representing the Song and it's properties*/
class Playlist
{
public:
    Playlist();
    void setSong(sf::SoundBuffer audio);
    sf::Sound* getSong();
    void playSong();
    void stopSong();

    static Playlist* readySongtoScene(sf::SoundBuffer* audio);

private:
    sf::SoundBuffer  mAudio;
    sf::Sound mSound;
};