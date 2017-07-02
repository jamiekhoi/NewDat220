//
// Created by Jack on 21.06.2017.
//

#ifndef GENERICWAVE_PISTOL_H
#define GENERICWAVE_PISTOL_H

#include <SFML/Graphics.hpp>
#include "Weapon.h"

class Pistol: public Weapon {
public:
    Pistol();
    void fire(std::vector<Bullet*>& bullets);
    void reload();
    void addAmmo();
    void draw(sf::RenderWindow &window);
    void setPosition(float x, float y);
    sf::Vector2f getPosition();
    void setRotation(double angle);
    void rotate(double angle);
    void setAnimationDirection(int direction);

protected:
    /*
    int ammo;
    int magazines;
    // Since Pistol is default weapon it should have infinite ammo. Change later.
    int maxMagazineCount = 99;
    int maxAmmoCount = 17;
    int damage = 5;
    // Should change to infinte range after a while
    int effectiveRange = 10000;
*/
    // Should these be in Weapon base class???
    /*
    sf::Texture weaponTexture;
    sf::Sprite weapon;

    sf::Texture* bulletTexture;
    sf::Sprite bullet;

    int weaponWidth = 80;
    int weaponHeight = 40;

    int bulletWidth = 5;
    int bulletHeight = 5;

    int currentDirectionAnimation;
     */

};


#endif //GENERICWAVE_PISTOL_H
