//
// Created by Jack on 21.06.2017.
//

#ifndef GENERICWAVE_WEAPON_H
#define GENERICWAVE_WEAPON_H

#include <cmath>
#include "Bullet.h"
#include "TestState.h"

const double pi = 3.14159265358979323846;

class Weapon {
public:
    Weapon(){}
    friend class Player;
    friend class TestState;
    virtual void fire(std::vector<Bullet*>& bullets){

        if(ammo > 0){
            // If that was last bullet
            if(--ammo == 0){
                // Reload if possible
                reload();
            }
            double angle = weapon.getRotation();
            double xdiff = cos(angle*pi/180.0) * weaponWidth;
            double ydiff = sin(angle*pi/180.0) * weaponHeight;

            // Position of pistol nozzle, i.e. where the bullet will be fired.
            double bulletx = weapon.getPosition().x + xdiff;
            double bullety = weapon.getPosition().y + ydiff;

            //std::cout << "xdiff: " << xdiff <<std::endl;
            //std::cout << "ydiff: " << ydiff << std::endl;

            Bullet* bullet = new Bullet();

            bullet->width = bulletWidth;
            bullet->height = bulletHeight;
            bullet->sprite.setTexture(*bulletTexture);
            bullet->setPosition(bulletx, bullety);

            bullet->penetration = weaponPenetration;
            bullet->damage = damage;
            bullet->effectiveRange = effectiveRange;
            bullet->speed = bulletSpeed;
            bullet->setAngle(angle);

            bullets.push_back(bullet);

        }
    }
    virtual void reload(){
        // Check for more magazines and reload if possible
        if(magazines != 0){
            magazines--;
            ammo = maxAmmoCount;
        }
    }
    virtual void addAmmo(){}
    virtual void draw(sf::RenderWindow &window){}
    virtual void setPosition(float x, float y){}
    virtual sf::Vector2f getPosition(){}
    virtual void setRotation(double angle){}
    virtual void rotate(double angle){}
    virtual void setAnimationDirection(int direction){}

protected:

    std::string name;

    int ammo;
    int magazines;
    // Since Pistol is default weapon it should have infinite ammo. Change later.
    int maxMagazineCount;
    int maxAmmoCount;
    int damage;
    // Should change to infinite range after a while
    int effectiveRange = 9999;

    sf::Texture weaponTexture;
    sf::Sprite weapon;

    sf::Texture* bulletTexture;

    int weaponWidth;
    int weaponHeight;

    int bulletWidth;
    int bulletHeight;

    int currentDirectionAnimation;

    int weaponPenetration = 1;

    double angle;

    int bulletSpeed = 3;
};



#endif //GENERICWAVE_WEAPON_H
