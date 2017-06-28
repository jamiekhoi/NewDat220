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
    void fire();
    void reload();
    void addAmmo();
    void draw(sf::RenderWindow &window);
    void setPosition(int x, int y);
    void setRotation(float angle);
    void rotate(float angle);

protected:
    int ammo;
    int magazines;
    // Since Pistol is default weapon it should have infinite ammo. Change later.
    int maxMagazineCount = 99;
    int maxAmmoCount = 17;
    int damage = 5;
    // Should change to infinte range after a while
    int effectiveRange = 10000;

    // Should these be in Weapon base class???
    sf::Texture weaponTexture;
    sf::Sprite weapon;

    sf::Texture bulletTexture;
    sf::Sprite bullet;

    int weaponWidth = 20;
    int weaponHeight = 20;

    int bulletWidth = 5;
    int bulletHeight = 5;

};


#endif //GENERICWAVE_PISTOL_H
