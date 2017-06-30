//
// Created by Jack on 21.06.2017.
//

#ifndef GENERICWAVE_WEAPON_H
#define GENERICWAVE_WEAPON_H


class Weapon {
public:
    Weapon(){}
    friend class Player;
    virtual void fire(){}
    virtual void reload(){}
    virtual void addAmmo(){}
    virtual void draw(sf::RenderWindow &window){}
    virtual void setPosition(float x, float y){}
    virtual sf::Vector2f getPosition(){}
    virtual void setRotation(double angle){}
    virtual void rotate(double angle){}
    virtual void setAnimationDirection(int direction){}

protected:
    sf::Texture weaponTexture;
    sf::Sprite weapon;

    sf::Texture bulletTexture;
    sf::Sprite bullet;

    int weaponWidth = 80;
    int weaponHeight = 40;

    int bulletWidth = 5;
    int bulletHeight = 5;

    int currentDirectionAnimation;
};


#endif //GENERICWAVE_WEAPON_H
