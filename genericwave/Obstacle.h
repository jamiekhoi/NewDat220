//
// Created by Jack on 25.06.2017.
//

#ifndef GENERICWAVE_OBSTACLE_H
#define GENERICWAVE_OBSTACLE_H

#include <SFML/Graphics.hpp>

class Obstacle: public sf::RectangleShape{
public:
    Obstacle() : sf::RectangleShape(){

    }

    // Extend base classes from sf::Rectangleshape
    void setPosition (float x, float y);
    void setSize(const sf::Vector2f &size);

protected:
    // Create hit-test objects for each side of the obstacle
    sf::RectangleShape left;
    sf::RectangleShape right;
    sf::RectangleShape top;
    sf::RectangleShape bottom;

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
    sf::RectangleShape left;
    sf::RectangleShape right;
    sf::RectangleShape top;
    sf::RectangleShape bottom;

};

#endif //GENERICWAVE_OBSTACLE_H
