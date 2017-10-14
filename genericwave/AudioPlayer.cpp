//
// Created by Jack on 14.10.2017.
//

#include <iostream>
#include "AudioPlayer.h"

AudioPlayer::AudioPlayer() {
    // load all sound effects
    sf::SoundBuffer* buffer = new sf::SoundBuffer;
    if (!buffer->loadFromFile("Audio/Effects/Kingdom Hearts Select.ogg")){
        std::cout << "Failed to load sound effect" << std::endl;
    }
    soundeffectlist.push_back(buffer);

    buffer = new sf::SoundBuffer;
    if (!buffer->loadFromFile("Audio/Effects/bump.ogg")){
        std::cout << "Failed to load sound effect" << std::endl;
    }
    soundeffectlist.push_back(buffer);

    // Song list
    songlist.push_back("Audio/Music/Rihanna/Desperado.flac");
    songlist.push_back("Audio/Music/Rihanna/James-Joint.flac");
    songlist.push_back("Audio/Music/WeAintThem.ogg");
    songlist.push_back("Audio/Music/Wonderland.ogg");

}

void AudioPlayer::playEffect(AudioPlayer::SoundEffects sound) {

    soundeffectplayer.setBuffer(*soundeffectlist[(std::size_t)sound]);
    soundeffectplayer.play();
}

void AudioPlayer::playSong(AudioPlayer::Songs song) {
    if (!songplayer.openFromFile(songlist[(std::size_t)song]))
        std::cout << "Could not open song" << std::endl;
    songplayer.play();
}

AudioPlayer::~AudioPlayer() {
    for(sf::SoundBuffer* buffer : soundeffectlist){
        delete buffer;
        buffer = nullptr;
    }
}
