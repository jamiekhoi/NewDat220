//
// Created by Jack on 21.06.2017.
//

#ifndef GENERICWAVE_PLAYER_H
#define GENERICWAVE_PLAYER_H

#include <SFML/Graphics.hpp>
#include <list>

#include "Weapon.h"

class Player {
public:
    Player();
    bool setTexture(sf::Texture texture);
    void setPosition(float x, float y);
    void process();
    void draw(sf::RenderWindow &window);
    bool checkCollision();
    sf::Sprite getsfSprite();
    void printPos();

    float getX() const;

    float getY() const;

protected:

    sf::Sprite sprite;
    sf::Texture texture;

    // Position of player
    float x, y;

    // Height and width of the player
    int height, width;

    int framecount, animations, currentframe, currentanimiation;
    sf::Clock clock;

    // Duration of one frame in ms
    int frameDuration;

    std::list<Weapon*> weapons;

    int currentWeaponNr;

    Weapon* currentWeapon;

};


#endif //GENERICWAVE_PLAYER_H
