//
// Created by Jack on 21.06.2017.
//

#ifndef GENERICWAVE_WEAPON_H
#define GENERICWAVE_WEAPON_H

#include <cmath>
#include "Bullet.h"
const double pi = 3.14159265358979323846;

class Weapon {
public:
    Weapon(){}
    friend class Player;
    virtual void fire(std::vector<Bullet*>& bullets){
        float angle = weapon.getRotation();
        float xdiff = cos(angle*pi/180.0) * weaponWidth;
        float ydiff = sin(angle*pi/180.0) * weaponHeight;

        // Position of pistol nozzle, i.e. where the bullet will be fired.
        float bulletx = weapon.getPosition().x + xdiff;
        float bullety = weapon.getPosition().y + ydiff;

        //std::cout << "xdiff: " << xdiff <<std::endl;
        //std::cout << "ydiff: " << ydiff << std::endl;

        Bullet* bullet = new Bullet();

        bullet->width = bulletWidth;
        bullet->height = bulletHeight;
        bullet->sprite.setTexture(*bulletTexture);

        bullet->penetration = weaponPenetration;
        bullet->damage = damage;
        bullet->effectiveRange = effectiveRange;
        bullet->speed = bulletSpeed;
        bullet->angle = angle;

        bullets.push_back(bullet);
    }
    virtual void reload(){}
    virtual void addAmmo(){}
    virtual void draw(sf::RenderWindow &window){}
    virtual void setPosition(float x, float y){}
    virtual sf::Vector2f getPosition(){}
    virtual void setRotation(double angle){}
    virtual void rotate(double angle){}
    virtual void setAnimationDirection(int direction){}

protected:

    int ammo;
    int magazines;
    // Since Pistol is default weapon it should have infinite ammo. Change later.
    int maxMagazineCount;
    int maxAmmoCount;
    int damage;
    // Should change to infinte range after a while
    int effectiveRange;

    sf::Texture weaponTexture;
    sf::Sprite weapon;

    sf::Texture* bulletTexture;

    int weaponWidth;
    int weaponHeight;

    int bulletWidth;
    int bulletHeight;

    int currentDirectionAnimation;

    int weaponPenetration;

    double angle;

    int bulletSpeed;
};


#endif //GENERICWAVE_WEAPON_H
