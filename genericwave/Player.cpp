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
    height = width = 0;

    // Starting position of the player.
    x = y = 50;
    sprite.setPosition(x, y);

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
    //std::cout << "IN PROCCESSS IN PLKAYER cLASS!!!!" << std::endl;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        // left key is pressed: move our character
        x -= 5;
        leftright = "left";
        currentanimiation = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        // Right key is pressed: move our character
        x += 5;
        leftright = "right";
        currentanimiation = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        // Up key is pressed: move our character
        updown = "up";
        y -= 5;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        // Down key is pressed: move our character
        y += 5;
        updown = "down";
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

const std::string &Player::getLeftright() const {
    return leftright;
}

void Player::setLeftright(const std::string &leftright) {
    Player::leftright = leftright;
}

const std::string &Player::getUpdown() const {
    return updown;
}

void Player::setUpdown(const std::string &updown) {
    Player::updown = updown;
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
    sf::FloatRect* temp = new sf::FloatRect(x, y, width, height);

    // Why doesnt this work?
    // this always returns false
    if(!a->getGlobalBounds().intersects(*temp)){
        return false;
    }

    while(a->left.getGlobalBounds().intersects(*temp)){
        move(-1, 0);
        temp = new sf::FloatRect(x, y, width, height);
    }
    while(a->right.getGlobalBounds().intersects(*temp)){
        move(1, 0);
        temp = new sf::FloatRect(x, y, width, height);
    }
    while(a->top.getGlobalBounds().intersects(*temp)){
        move(0, -1);
        temp = new sf::FloatRect(x, y, width, height);
    }
    while(a->bottom.getGlobalBounds().intersects(*temp)){
        move(0, 1);
        temp = new sf::FloatRect(x, y, width, height);
    }

    return a->getGlobalBounds().intersects(*temp);
}

bool Player::checkPointCollision(sf::Vector2f point) {
    // Just to be safe (Problem in Player::CheckCollision). Nevermind.
    //sf::FloatRect* temp = new sf::FloatRect(x, y, width, height);
    if(sprite.getGlobalBounds().contains(point)){
        return true;
    }else {
        return false;
    }
}
