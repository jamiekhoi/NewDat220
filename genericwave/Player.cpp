//
// Created by Jack on 21.06.2017.
//

#include <iostream>

#include "Player.h"
#include "Pistol.h"

Player::Player() {
    if (!texture.loadFromFile("Bilder/Player/TestPlayer.png"))
    {
        std::cout << "Failed to load Player texture" << std::endl;
    }
    sprite.setTexture(texture);

    sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));

    // Two animations for the player, left facing animation and right facing animation.
    animations = 2;

    // Two frames per animation.
    framecount = 2;


    currentframe = 0;
    currentanimiation = 0;

    // Height and width of a frame for the character.
    height = width = 50;

    // Starting position of the player.
    x = y = 500;

    frameDuration = 700;

    currentWeaponNr = 0;
    currentWeapon = new Pistol();
    weapons.push_back(currentWeapon);
}

bool Player::setTexture(sf::Texture texture) {
    this->texture = texture;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));

    return true;
}

void Player::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Player::process() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        // left key is pressed: move our character
        x -= 5;
        currentanimiation = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        // Right key is pressed: move our character
        x += 5;
        currentanimiation = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        // Up key is pressed: move our character
        y -= 5;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        // Down key is pressed: move our character
        y += 5;
    }
    sprite.setPosition(x, y);

    // Go to next animation frame if required
    if (clock.getElapsedTime().asMilliseconds() < frameDuration)
        return;

    if (++currentframe >= framecount){
        currentframe = 0;
    }

    sprite.setTextureRect(sf::IntRect(currentframe*50, currentanimiation*50, 50, 50));

    clock.restart();
}
