//
// Created by Jack on 21.06.2017.
//

#ifndef GENERICWAVE_WEAPON_H
#define GENERICWAVE_WEAPON_H


class Weapon {
public:
    Weapon(){}
    virtual void fire(){}
    virtual void reload(){}
    virtual void addAmmo(){}
    virtual void draw(sf::RenderWindow &window){}
    virtual void setPosition(int x, int y){}
    virtual void setRotation(float angle){}
    virtual void rotate(float angle){}
};


#endif //GENERICWAVE_WEAPON_H
