//
// Created by Jack on 25.06.2017.
//

#include "Obstacle.h"

void Obstacle::setPosition(float x, float y) {
    // setSize must be call first for side variables to be positioned correctly.
    sf::RectangleShape::setPosition(x, y);
    left.setPosition(x, y);
    right.setPosition(x + getSize().x , y);

}

void Obstacle::setSize(const sf::Vector2f &size) {
    sf::RectangleShape::setSize(size);
    left.setSize(sf::Vector2f(1, size.y));
    right.setSize(sf::Vector2f(1, size.y));
    top.setSize(sf::Vector2f(size.x, 1));
    bottom.setSize(sf::Vector2f(size.x, 1));

}
