//
// Created by Jack on 01.07.2017.
//

#ifndef GENERICWAVE_BULLET_H
#define GENERICWAVE_BULLET_H


#include <SFML/Graphics.hpp>
#include "Obstacle.h"

class Enemy;

class Bullet {
public:
    friend class Weapon;
    Bullet(){}
    void move();
    void draw(sf::RenderWindow & window);
    void setAngle(double angle);
    void setPosition(double x, double y);
    bool checkCollisionObs(Obstacle* obs);
    bool checkCollisionEnemy(Enemy* en);
    bool hit();
    int getDamage();

protected:
    float width;
    float height;
    double speed;
    double xspeed;
    double yspeed;
    int damage;
    int penetration;
    int effectiveRange;
    double angle;
    sf::Sprite sprite;
    double x, y;
};


#endif //GENERICWAVE_BULLET_H
