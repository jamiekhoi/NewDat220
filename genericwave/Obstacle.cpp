//
// Created by Jack on 25.06.2017.
//

#include "Obstacle.h"

void Obstacle::setPosition(float x, float y) {
    // setSize must be call first for side variables to be positioned correctly.
    sf::RectangleShape::setPosition(x, y);
    left.setPosition(x, y);
    right.setPosition(x + getSize().x , y);
    top.setPosition(x, y);
    bottom.setPosition(x, y + getSize().y);

}

void Obstacle::setSize(const sf::Vector2f &size) {
    sf::RectangleShape::setSize(size);
    left.setSize(sf::Vector2f(thickness, size.y));
    right.setSize(sf::Vector2f(thickness, size.y));
    top.setSize(sf::Vector2f(size.x, thickness));
    bottom.setSize(sf::Vector2f(size.x, thickness));

}

void Obstacle::draw(sf::RenderWindow& window) {
    window.draw(*this);
    window.draw(left);
    window.draw(right);
    window.draw(top);
    window.draw(bottom);
}

void Obstacle2::setPosition(float x, float y) {
    // setSize must be call first for side variables to be positioned correctly.
    left = x;
    top = y;

    //left.setPosition(x, y);
    h_left.left = x;
    h_left.top = y;
    //right.setPosition(x + getSize().x , y);
    h_right.left = x + width;
    h_right.top = y;
    //top.setPosition(x, y);
    h_top.left = x;
    h_top.top = y;
    //bottom.setPosition(x, y + getSize().y);
    h_bottom.left = x;
    h_bottom.top = y + height;
}

void Obstacle2::setSize(const sf::Vector2f &size) {
    width = size.x;
    height = size.y;

    h_left.width = thickness;
    h_left.height = size.y;

    h_right.width = thickness;
    h_right.height = size.y;

    h_top.width = size.x;
    h_top.height = thickness;

    h_bottom.width = size.x;
    h_bottom.height = thickness;
}
