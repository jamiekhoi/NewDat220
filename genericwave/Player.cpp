//
// Created by Jack on 21.06.2017.
//

#include <iostream>
#include <cmath>

#include "Player.h"
#include "Pistol.h"

Player::Player() {
    if (!texture.loadFromFile("Bilder/Player/TestPlayer2.png"))
    {
        std::cout << "Failed to load Player texture" << std::endl;
    }
    sprite.setTexture(texture);


    // Height and width of a frame for the character.
    height = 210;
    width = 140;

    sprite.setTextureRect(sf::IntRect(0, 0, width, height));

    // Two animations for the player, left facing animation and right facing animation.
    animations = 2;

    // Two frames per animation.
    framecount = 2;


    currentframe = 0;
    currentDirectionAnimation = 0;

    // Starting position of the player.
    x = y = 500;
    sprite.setPosition(x, y);

    frameDuration = 700;

    // Create default weapon
    currentWeaponNr = 0;
    currentWeapon = new Pistol();
    weapons.push_back(currentWeapon);
}

bool Player::setTexture(sf::Texture texture) {
    this->texture = texture;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, width, height));

    return true;
}

void Player::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
}

void Player::draw(sf::RenderWindow &window) {

    // Update weapon position
    currentWeapon->setPosition(x,y);

    // Get direction mouse is pointing in
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::Vector2f weaponPos = currentWeapon->getPosition();

    // Radians and angle are going clockwise, where direectly right = 0
    double radians = atan2(mousePos.y - weaponPos.y, mousePos.x - weaponPos.x);
    double angle = (radians*180)/3.14159265358979323846;

    std::cout << angle << std::endl;

    // Set weapon to mouse direction
    currentWeapon->setRotation(-45 + angle);

    // Update Player direction sprite


    // Draw current weapon
    currentWeapon->draw(window);

    // Draw Player
    window.draw(sprite);
}

void Player::process() {
    //std::cout << "IN PROCCESSS IN PLKAYER cLASS!!!!" << std::endl;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        // left key is pressed: move our character
        x -= 5;
        currentDirectionAnimation = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        // Right key is pressed: move our character
        x += 5;
        currentDirectionAnimation = 1;
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

    sprite.setTextureRect(sf::IntRect(currentframe*width, currentDirectionAnimation*height, width, height));

    clock.restart();
}

sf::Sprite Player::getsfSprite() {
    return sprite;
}

void Player::printPos() {
    std::cout << "Player positions (variable): " << x << ", " << y << std::endl;
    std::cout << "Player sprite position: " << sprite.getPosition().x << ", " << sprite.getPosition().y << std::endl;
}

float Player::getX() const {
    return x;
}

float Player::getY() const {
    return y;
}

void Player::move(float x, float y) {

    this->x += x;
    this->y += y;
    sprite.setPosition(x, y);
}

bool Player::checkCollision(Obstacle *a) {
    // Create a new sf::FloatRect to test collision
    // For some reason the sf::sprite's .getGlobalBounds() doesn't update right away.
    // but the sf::sprite's info(position) is.
    // Should I be using pointer for this? Can I use normal variable?
    sf::FloatRect* temp = new sf::FloatRect(x, y, width, height);

    if(!a->getGlobalBounds().intersects(*temp)){
        delete temp;
        return false;
    }

    while(a->left.getGlobalBounds().intersects(*temp)){
        move(-1, 0);
        temp->left -= 1;
    }

    while(a->right.getGlobalBounds().intersects(*temp)){
        move(1, 0);
        temp->left += 1;
    }

    while(a->top.getGlobalBounds().intersects(*temp)){
        move(0, -1);
        temp->top -= 1;
    }

    while(a->bottom.getGlobalBounds().intersects(*temp)) {
        move(0, 1);
        temp->top += 1;
    }


    bool b = a->getGlobalBounds().intersects(*temp);
    delete temp;

    return b;
}

bool Player::checkPointCollision(sf::Vector2f point) {
    // Just to be safe (Problem in Player::CheckCollision). Nevermind.
    //sf::FloatRect* temp = new sf::FloatRect(x, y, width, height);
    return sprite.getGlobalBounds().contains(point);
}

bool Player::fireWeapon() {
    currentWeapon->fire();
    return false;
}
