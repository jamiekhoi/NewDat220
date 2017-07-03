//
// Created by Jack on 01.07.2017.
//

#ifndef GENERICWAVE_BULLET_H
#define GENERICWAVE_BULLET_H


#include <SFML/Graphics.hpp>
#include "Obstacle.h"

class Bullet {
public:
    friend class Weapon;
    Bullet(){}
    void move();
    void draw(sf::RenderWindow & window);
    void setAngle(double angle);
    void setPosition(int x, int y);
    bool checkCollisionObs(Obstacle* obs);
    bool hit();

protected:
    float width;
    float height;
    float speed;
    float xspeed;
    float yspeed;
    int damage;
    int penetration;
    int effectiveRange;
    double angle;
    sf::Sprite sprite;
    int x, y;
};


#endif //GENERICWAVE_BULLET_H
