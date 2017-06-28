//
// Created by Jack on 21.06.2017.
//

#include "Pistol.h"
#include <iostream>

Pistol::Pistol() {

    if (!weaponTexture.loadFromFile("Bilder/Player/TestPlayer.png"))
    {
        std::cout << "Failed to load Weapon texture" << std::endl;
    }
    weapon.setTexture(weaponTexture);
    weapon.setTextureRect(sf::IntRect(0, 0, weaponWidth, weaponHeight));

    if (!bulletTexture.loadFromFile("Bilder/Player/TestPlayer.png"))
    {
        std::cout << "Failed to load Bullet texture" << std::endl;
    }
    bullet.setTexture(bulletTexture);
    bullet.setTextureRect(sf::IntRect(0, 55, bulletWidth, bulletHeight));

}

void Pistol::fire() {
    // Should take in a list of live bullets as a parameter
    // Create a new bullet
    // Posistion of bullet is tip of gun
    // Bullet should move angle

}

void Pistol::reload() {

}

void Pistol::addAmmo() {

}

void Pistol::setPosition(int x, int y) {
    weapon.setPosition(x, y);
}

void Pistol::setRotation(double angle) {
    weapon.setRotation(angle);
}

void Pistol::rotate(double angle) {
    weapon.rotate(angle);
}

void Pistol::draw(sf::RenderWindow &window) {
    window.draw(weapon);
}

sf::Vector2f Pistol::getPosition() {
    return weapon.getPosition();
}
