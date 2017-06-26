//
// Created by Jack on 21.06.2017.
//

#ifndef GENERICWAVE_PLAYER_H
#define GENERICWAVE_PLAYER_H

#include <SFML/Graphics.hpp>
#include <list>

#include "Weapon.h"
#include "Obstacle.h"

class Player {
public:
    Player();
    bool setTexture(sf::Texture texture);
    void setPosition(float x, float y);
    void move(float x, float y);
    void process();
    void draw(sf::RenderWindow &window);
    bool checkCollision(Obstacle* a);

    sf::Sprite getsfSprite();
    void printPos();
    bool collisionWithPlayer();
    bool collisionWithPlayer(int i);


    float getX() const;

    float getY() const;

    const std::string &getLeftright() const;

    void setLeftright(const std::string &leftright);

    const std::string &getUpdown() const;

    void setUpdown(const std::string &updown);

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

    // Last direction moved
    std::string leftright = "";
    std::string updown = "";

};


#endif //GENERICWAVE_PLAYER_H
