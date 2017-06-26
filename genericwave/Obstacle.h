//
// Created by Jack on 25.06.2017.
//

#ifndef GENERICWAVE_OBSTACLE_H
#define GENERICWAVE_OBSTACLE_H

#include <SFML/Graphics.hpp>

class Obstacle: public sf::RectangleShape{
public:
    Obstacle() : sf::RectangleShape(){
        left.setFillColor(sf::Color::Magenta);
        right.setFillColor(sf::Color::Magenta);
        top.setFillColor(sf::Color::Magenta);
        bottom.setFillColor(sf::Color::Magenta);

    }

    // Extend base classes from sf::Rectangleshape
    void setPosition (float x, float y);
    void setSize(const sf::Vector2f &size);
    void draw(sf::RenderWindow& window);

    // Create hit-test objects for each side of the obstacle
    sf::RectangleShape left;
    sf::RectangleShape right;
    sf::RectangleShape top;
    sf::RectangleShape bottom;

protected:

    int thickness = 2;

};


class Obstacle2: public sf::FloatRect{
public:
    Obstacle2() : sf::FloatRect(){

    }

    // Extend base classes from sf::Rectangleshape
    void setPosition (float x, float y);
    void setSize(const sf::Vector2f &size);

protected:
    // Create hit-test objects for each side of the obstacle
    sf::FloatRect h_left;
    sf::FloatRect h_right;
    sf::FloatRect h_top;
    sf::FloatRect h_bottom;

    int thickness = 1;
};

#endif //GENERICWAVE_OBSTACLE_H
