//
// Created by Jack on 19.08.2017.
//

#ifndef GENERICWAVE_AUTOMATICWEAPON_H
#define GENERICWAVE_AUTOMATICWEAPON_H


#include "../Weapon.h"

class AutomaticWeapon: public Weapon {
public:
    AutomaticWeapon();
    void fire(std::vector<Bullet*>& bullets);
    void reload();
    void addAmmo();
    void draw(sf::RenderWindow &window);
    void setPosition(float x, float y);
    sf::Vector2f getPosition();
    void setRotation(double angle);
    void rotate(double angle);
    void setAnimationDirection(int direction);
    bool holdFire();
};


#endif //GENERICWAVE_AUTOMATICWEAPON_H
