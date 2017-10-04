//
// Created by Jack on 03.07.2017.
//

#ifndef GENERICWAVE_ENEMY_H
#define GENERICWAVE_ENEMY_H

#include <SFML/Graphics.hpp>
#include "Obstacle.h"
#include "Player.h"

class Enemy {
public:
    friend class TestState;
    friend class Bullet;
    Enemy();
    void move(sf::Vector2f playerPos);
    void draw(sf::RenderWindow &window);
    bool checkCollisionObs(Obstacle* ob);
    bool checkCollisionPlayer(Player* player);
    void setPosition(int x, int y);
    void setSize(int width, int height);
    bool dead(int damage);


protected:
    sf::Texture* texture;
    sf::Sprite sprite;

    int points;

    int health;
    // Position of Enemy
    float x, y;

    // Speed
    float xspeed;
    float yspeed;
    float speed;

    // Height and width of enemy
    int height, width;

    int movements = 0;
    int movementmax = 6;

    int framecount;
    int animations;

    int currentframe;
    int currentDirectionAnimation;

};


#endif //GENERICWAVE_ENEMY_H
