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

    // Run from the state. Where the player moves
    void process();

    void draw(sf::RenderWindow &window);

    // Fire weapon if possible
    bool fireWeapon();

    bool checkCollision(Obstacle* a);
    bool checkPointCollision(sf::Vector2f point);

    sf::Sprite getsfSprite();
    void printPos();

    std::ostream& operator<<(std::ostream& stream){
        stream << "Player pos: (" << x << ", " << y << ")" << std::endl;
        stream << "Frame count: " << framecount << std::endl;
        return stream;

    }

    bool collisionWithPlayer();
    bool collisionWithPlayer(int i);


    float getX() const;

    float getY() const;


protected:

    sf::Sprite sprite;
    sf::Texture texture;

    // Position of player
    float x, y;

    // Height and width of the player
    int height, width;

    int framecount, animations, currentframe, currentDirectionAnimation;
    sf::Clock clock;

    // Duration of one frame in ms
    int frameDuration;

    std::list<Weapon*> weapons;

    int currentWeaponNr;

    Weapon* currentWeapon;

};


#endif //GENERICWAVE_PLAYER_H
