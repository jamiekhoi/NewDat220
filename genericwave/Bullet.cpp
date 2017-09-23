//
// Created by Jack on 01.07.2017.
//

#include <cmath>
#include <iostream>
#include "Bullet.h"
#include "Enemy.h"


void Bullet::setAngle(long double angle) {
    this->angle = angle;
    xspeed = cos(angle*pi/180.0) * speed;
    yspeed = sin(angle*pi/180.0) * speed;

}

void Bullet::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Bullet::move() {
    x += xspeed;
    y += yspeed;
    sprite.setPosition(x, y);

}

void Bullet::setPosition(long double x, long double y) {
    this->x = x;
    this->y = y;
    this->sprite.setPosition(x, y);

}

bool Bullet::checkCollisionObs(Obstacle * obs) {

    return sprite.getGlobalBounds().intersects(obs->getGlobalBounds());
}

bool Bullet::hit() {
    //std::cout << "hit" << std::endl;
    penetration--;
    // Return true if bullet can no longer penetrate object
    return penetration < 1;
}

bool Bullet::checkCollisionEnemy(Enemy *en) {
    return sprite.getGlobalBounds().intersects(en->sprite.getGlobalBounds());
}

int Bullet::getDamage() {
    return damage;
}
