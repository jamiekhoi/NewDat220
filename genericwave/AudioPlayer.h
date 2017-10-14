//
// Created by Jack on 14.10.2017.
//

#ifndef GENERICWAVE_AUDIOPLAYER_H
#define GENERICWAVE_AUDIOPLAYER_H


#include <SFML/Audio.hpp>

class AudioPlayer {
public:
    AudioPlayer();
    ~AudioPlayer();
    enum class SoundEffects {SELECT, BUMP};
    enum class Songs {RIHANNA, RIHANNA2, CHILDISH, SWIFT};

    void playEffect(SoundEffects sound);
    void playSong(Songs song);
protected:
    sf::Sound soundeffectplayer;
    sf::SoundBuffer bumpBuffer;
    sf::SoundBuffer selectBuffer;
    std::vector<sf::SoundBuffer*> soundeffectlist;

    sf::Music songplayer;
    std::vector<std::string> songlist;


};


#endif //GENERICWAVE_AUDIOPLAYER_H
