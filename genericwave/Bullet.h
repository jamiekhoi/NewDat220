//
// Created by Jack on 01.07.2017.
//

#ifndef GENERICWAVE_BULLET_H
#define GENERICWAVE_BULLET_H


#include <SFML/Graphics.hpp>

class Bullet {
public:
    friend class Weapon;
    Bullet(){}
    Bullet(int width, int height, int speed, int damage, int penetration = 1);
    void move();
    void draw();
    void setTexture(sf::Texture);

protected:
    float width;
    float height;
    float speed;
    int damage;
    int penetration;
    int effectiveRange;
    double angle;
    sf::Sprite sprite;
};


#endif //GENERICWAVE_BULLET_H
