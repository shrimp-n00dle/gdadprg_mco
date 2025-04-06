#include "Playlist.hpp"

Playlist::Playlist() {}

void Playlist::setSong(sf::SoundBuffer audio)
{
    mAudio = audio;
    mSound.setBuffer(mAudio);

}

sf::Sound* Playlist::getSong()
{
    return &mSound;
}

void Playlist::playSong()
{
    mSound.play();
    
}

void Playlist::stopSong()
{
    mSound.stop();

}

Playlist* Playlist::readySongtoScene(sf::SoundBuffer* audio)
{
    Playlist* playlist = new Playlist();
    playlist->setSong(*audio);

    return playlist;
}