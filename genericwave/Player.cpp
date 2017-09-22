//
// Created by Jack on 21.06.2017.
//

#include <iostream>
#include <cmath>

#include "Player.h"
#include "Weapons/Pistol.h"
#include "Bullet.h"
#include "Weapons/AutomaticWeapon.h"


Player::Player() {
    if (!texture.loadFromFile("Bilder/Player/TestPlayer2scaleddown.png"))
    {
        std::cout << "Failed to load Player texture" << std::endl;
    }
    sprite.setTexture(texture);

    // Height and width of a frame for the character. According to player image
    height = 105;
    width = 70;

    // Set texture part
    sprite.setTextureRect(sf::IntRect(0, 0, width, height));

    // Scale player if needed. Done manually
    //sprite.scale(0.5, 0.5);

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
    currentWeapon = new AutomaticWeapon();
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

    // Get direction mouse is pointing in
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    // Radians and angle are going clockwise, where direectly right = 0
    double radians = atan2(mousePos.y - (y + height/2), mousePos.x - (x + width/2));
    //double radians = atan2(weaponPos.y - mousePos.y, weaponPos.x - mousePos.x);
    //if(radians < 0){ radians += pi; }
    //radians += pi/2;
    double angle = (radians*180)/pi;

    //std::cout << angle << std::endl;

    // Set correct animation direction for player
    currentDirectionAnimation = angle < 90 && angle > -90 ? 1 : 0;
    sprite.setTextureRect(sf::IntRect(currentframe*width, currentDirectionAnimation*height, width, height));

    // Set correct animation direction for weapon
    currentWeapon->setAnimationDirection(currentDirectionAnimation);

    // Update weapon position
    if(currentDirectionAnimation == 0) // Facing left
    {
        currentWeapon->setPosition(x + (width/4) , y + height/2);
        //currentWeapon->setPosition(x, y + height/2);
    }else // Facing right
    {
        currentWeapon->setPosition(x + (width*3)/4, y + height/2);
    }

    // Set weapon to mouse direction
    currentWeapon->setRotation(angle);
    currentWeapon->angle = angle;

    // Draw current weapon
    currentWeapon->draw(window);

    // Draw Player
    window.draw(sprite);
}

void Player::process() {
    int xdiff = 0;
    int ydiff = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        // left key is pressed: move our character
        xdiff -= 5;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        // Right key is pressed: move our character
        xdiff += 5;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        // Up key is pressed: move our character
        ydiff -= 5;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        // Down key is pressed: move our character
        ydiff += 5;
    }

    x += xdiff;
    y += ydiff;

    // Check if there was any movement
    if(xdiff != 0 || ydiff != 0){
        movements++;

    }


    sprite.setPosition(x, y);

    // Go to next animation frame if required
    if (movements > movementmax){
        movements = 0;
        if (++currentframe >= framecount){
            currentframe = 0;
        }
    }

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

    while(a->getGlobalBounds().intersects(*temp)){
        if(a->left.getGlobalBounds().intersects(*temp)){
            move(-1, 0);
            temp->left -= 1;
        }

        if(a->right.getGlobalBounds().intersects(*temp)){
            move(1, 0);
            temp->left += 1;
        }

        if(a->top.getGlobalBounds().intersects(*temp)){
            move(0, -1);
            temp->top -= 1;
        }

        if(a->bottom.getGlobalBounds().intersects(*temp)) {
            move(0, 1);
            temp->top += 1;
        }
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

bool Player::fireWeapon(std::vector<Bullet*>& bullets) {
    currentWeapon->fire(bullets);
    return false;
}

sf::Vector2f Player::getPosition() {
    return sf::Vector2f(x, y);
}

void Player::addWeapon() {

}

void Player::switchWeapon(int weaponPos) {
    currentWeaponNr = weaponPos;
    currentWeapon = weapons[weaponPos];
}
