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
    if (!Map::load("Bilder/Stages/TMX/teststage3.json", objects))
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
    for (Object* object : objects)
    {
        object->draw(machine->getWindow());
    }
    player->process();
    // Crude. Actually centers around player sprite's upper left corner
    sf::View tempView = machine->getWindow().getView();
    float tempx = player->getX();
    float tempy = player->getY();
    tempView.setCenter(tempx, tempy);
    player->draw(machine->getWindow());
    machine->getWindow().setView(tempView);
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


