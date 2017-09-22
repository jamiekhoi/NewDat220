//
// Created by Jack on 19.08.2017.
//

#include <iostream>
#include "AutomaticWeapon.h"

AutomaticWeapon::AutomaticWeapon() {
    name = "automatic";

    // Weapon specific info
    firemode = "auto";
    weaponWidth = 80;
    weaponHeight = 40;

    bulletWidth = 5;
    bulletHeight = 5;

    maxAmmoCount = 30;
    ammo = maxAmmoCount;
    maxMagazineCount = 10;
    magazines = maxMagazineCount;

    bulletSpeed = 20;
    damage = 5;
    effectiveRange = 9999;

    weaponPenetration = 5;

    if (!weaponTexture.loadFromFile("Bilder/Weapons/pistola.png"))
    {
        std::cout << "Failed to load Weapon texture" << std::endl;
    }
    weapon.setTexture(weaponTexture);
    currentDirectionAnimation = 0;
    weapon.setTextureRect(sf::IntRect(0, currentDirectionAnimation*weaponHeight, weaponWidth, weaponHeight));

    // Is this correct?
    bulletTexture = new sf::Texture();
    if (!bulletTexture->loadFromFile("Bilder/Weapons/pistolbullet.png"))
    {
        std::cout << "Failed to load Bullet texture" << std::endl;
    }
}

void AutomaticWeapon::fire(std::vector<Bullet *> &bullets) {
    // Should take in a list of live bullets as a parameter
    // Create a new bullet
    // Posistion of bullet is tip of gun
    // Bullet should move angle
    Weapon::fire(bullets);
}

void AutomaticWeapon::reload() {
    Weapon::reload();
}

void AutomaticWeapon::addAmmo() {

}

void AutomaticWeapon::draw(sf::RenderWindow &window) {
    Weapon::draw(window);
}

void AutomaticWeapon::setPosition(float x, float y) {
    Weapon::setPosition(x, y);
}

sf::Vector2f AutomaticWeapon::getPosition() {
    return Weapon::getPosition();
}

void AutomaticWeapon::setRotation(double angle) {
    Weapon::setRotation(angle);
}

void AutomaticWeapon::rotate(double angle) {
    Weapon::rotate(angle);
}

void AutomaticWeapon::setAnimationDirection(int direction) {
    Weapon::setAnimationDirection(direction);
}

void AutomaticWeapon::holdFire(std::vector<Bullet*>& bullets) {
    Weapon::holdFire(bullets);
}
