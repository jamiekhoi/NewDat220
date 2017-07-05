//
// Created by Jack on 21.06.2017.
//

#include "Pistol.h"
#include "Bullet.h"
#include <iostream>
#include <cmath>

Pistol::Pistol() {

    // Weapon specific info
    weaponWidth = 80;
    weaponHeight = 40;

    bulletWidth = 5;
    bulletHeight = 5;

    ammo = 1;
    maxAmmoCount = 17;
    magazines = 1;
    maxMagazineCount = 99;

    bulletSpeed = 20;
    damage = 5;
    effectiveRange = 9999;

    weaponPenetration = 1;

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
    //bullet.setTexture(*bulletTexture);
    //bullet.setTextureRect(sf::IntRect(0, 55, bulletWidth, bulletHeight));

}

void Pistol::fire(std::vector<Bullet*>& bullets) {
    // Should take in a list of live bullets as a parameter
    // Create a new bullet
    // Posistion of bullet is tip of gun
    // Bullet should move angle
    Weapon::fire(bullets);

}

void Pistol::reload() {

}

void Pistol::addAmmo() {

}

void Pistol::setPosition(float x, float y) {
    weapon.setPosition(x, y);
}

void Pistol::setRotation(double angle) {
    weapon.setRotation(angle);
}

void Pistol::rotate(double angle) {
    weapon.rotate(angle);
}

void Pistol::draw(sf::RenderWindow &window) {
    //std::cout << currentDirectionAnimation << std::endl;

    window.draw(weapon);
}

sf::Vector2f Pistol::getPosition() {
    return weapon.getPosition();
}

void Pistol::setAnimationDirection(int direction) {
    currentDirectionAnimation = direction;
    weapon.setTextureRect(sf::IntRect(0, currentDirectionAnimation*weaponHeight, weaponWidth, weaponHeight));
}
