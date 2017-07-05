//
// Created by Jack on 03.07.2017.
//

#include <iostream>
#include "Enemy.h"

Enemy::Enemy() {

    texture = new sf::Texture;
    if (!texture->loadFromFile("Bilder/Player/TestPlayer2scaleddown.png"))
    {
        std::cout << "Failed to load Player texture" << std::endl;
    }
    sprite.setTexture(*texture);

    // Height and width of a frame for the enemy
    width = 70;
    height = 105;

    // Set texture part
    sprite.setTextureRect(sf::IntRect(0, 0, width, height));

    // Two animations for the player, left facing animation and right facing animation.
    animations = 2;

    // Two frames per animation.
    framecount = 2;

    currentframe = 0;
    currentDirectionAnimation = 0;

    // Starting position of the player.
    x = 50;
    y = 500;
    sprite.setPosition(x, y);

    xspeed = 5;
    yspeed = 5;
    speed = 3;

    health = 5;
}

void Enemy::move(sf::Vector2f playerPos) {

    float xdiff = playerPos.x - x;
    float ydiff = playerPos.y - y;
    double radians = atan2(ydiff, xdiff);

    // Set/change enemy animation of needed
    movements++;
    // Go to next animation frame if required
    if (movements > movementmax){
        movements = 0;
        if (++currentframe >= framecount){
            currentframe = 0;
        }
    }

    if(xdiff < 0){
        currentDirectionAnimation = 0; // Facing left
    }else{
        currentDirectionAnimation = 1; // Facing right
    }

    y += sin(radians)*speed;
    x += cos(radians)*speed;
    sprite.setPosition(x, y);
}

void Enemy::draw(sf::RenderWindow &window) {
    // Better to put this in Enemy::move()
    sprite.setTextureRect(sf::IntRect(currentframe*width, currentDirectionAnimation*height, width, height));

    window.draw(sprite);
}

bool Enemy::checkCollisionObs(Obstacle *ob) {
    // Create a new sf::FloatRect to test collision
    // For some reason the sf::sprite's .getGlobalBounds() doesn't update right away.
    // but the sf::sprite's info(position) is.
    // Should I be using pointer for this? Can I use normal variable?
    sf::FloatRect* temp = new sf::FloatRect(x, y, width, height);

    if(!ob->getGlobalBounds().intersects(*temp)){
        delete temp;
        return false;
    }

    while(ob->getGlobalBounds().intersects(*temp)){
        bool fuckyou = true;
        if(ob->left.getGlobalBounds().intersects(*temp)){
            x--;
            temp->left -= 1;
            fuckyou = false;
        }

        if(ob->right.getGlobalBounds().intersects(*temp)){
            x++;
            temp->left += 1;
            fuckyou = false;
        }

        if(ob->top.getGlobalBounds().intersects(*temp)){
            y--;
            temp->top -= 1;
            fuckyou = false;
        }

        if(ob->bottom.getGlobalBounds().intersects(*temp)) {
            y++;
            temp->top += 1;
            fuckyou = false;
        }

        if(fuckyou){
            break;
        }

    }

    sprite.setPosition(x, y);
    delete temp;

    return false;
}

bool Enemy::checkCollisionPlayer(Player player) {
    return false;
}

void Enemy::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
    sprite.setPosition(x, y);

}

void Enemy::setSize(int width, int height) {
    this->width = width;
    this->height = height;
    this->sprite.setTextureRect(sf::IntRect(0, 0, width, height));
}

bool Enemy::dead(int damage) {
    health -= damage;
    return health < 1;
}
