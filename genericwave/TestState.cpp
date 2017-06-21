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
    if (!Map::load("Bilder/Stages/TMX/teststage2.json", objects))
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
    player->draw(machine->getWindow());
    machine->getWindow().display();
}

void TestState::handleEvent(sf::Event &event) {

}

void TestState::setMachine(GameMachine *machine) {
    this->machine = machine;
}

void TestState::extrafunc(std::string command) {
    State::extrafunc(command);
}


