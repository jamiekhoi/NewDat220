//
// Created by Jack on 18.06.2017.
//

#include "TestState.h"
#include "map.h"
#include <iostream>
#include "object.h"
#include "Player.h"

TestState::TestState() {
// Load map information from JSON into object list
    if (!Map::load("Bilder/Stages/TMX/teststage3.json", objects, obstacles))
    {
        std::cout << "Failed to load map data." << std::endl;
    }

    player = new Player();

    /*
    // Standard SFML setup
    window.create(sf::VideoMode(640, 480), "Mario?");

    // Double the size of the screen
    sf::View view = window.getDefaultView();
    view.setSize(view.getSize().x / 2, view.getSize().y / 2);
    view.setCenter(view.getCenter().x / 2, view.getCenter().y / 2);
    window.setView(view);
     */
}

void TestState::Running() {
    machine->getWindow().clear(sf::Color::Black);

    // Draw the map
    for (Object* object : objects)
    {
        object->draw(machine->getWindow());
    }

    // Move the user, ect.
    player->process();

    // Draw the user
    player->draw(machine->getWindow());

    //std::cout << "OBSTACLE SIZE: " << obstacles.size() << std::endl;
    // For testing. Drawing obstacles
    for(sf::RectangleShape* obstacle: obstacles)
    {
        //std::cout << "OBSTACLE" << std::endl;
        machine->getWindow().draw(*obstacle);
    }

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(100, 50));
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setPosition(10, 20);
    machine->getWindow().draw(rectangle);

    // Set the view (what the user sees of the game map)
    // Crude. Actually centers around player sprite's upper left corner
    sf::View tempView = machine->getWindow().getView();
    float tempx = player->getX();
    float tempy = player->getY();
    tempView.setCenter(tempx, tempy);
    machine->getWindow().setView(tempView);

    // Draw the screen
    machine->getWindow().display();
}

void TestState::handleEvent(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed)
    {
        player->printPos();
        sf::Vector2f worldPos = machine->getWindow().mapPixelToCoords(sf::Mouse::getPosition(machine->getWindow()));
        std::cout << "Relative Mouse pos" << std::endl << "x: " << worldPos.x << "\ty: " << worldPos.y << std::endl << std::endl;
        std::cout << "Real Mouse pos" << std::endl << "x: " << sf::Mouse::getPosition(machine->getWindow()).x << "\ty: " << sf::Mouse::getPosition(machine->getWindow()).y << std::endl << std::endl;
    }
}

void TestState::setMachine(GameMachine *machine) {
    this->machine = machine;
}

void TestState::extrafunc(std::string command) {
    State::extrafunc(command);
}


