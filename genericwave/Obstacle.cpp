//
// Created by Jack on 25.06.2017.
//

#include "Obstacle.h"

void Obstacle::setPosition(float x, float y) {
    sf::RectangleShape::setPosition(x, y);
}

void Obstacle::setSize(const sf::Vector2f &size) {
    sf::RectangleShape::setSize(size);
}
