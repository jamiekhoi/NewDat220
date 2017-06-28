//
// Created by Jack on 18.06.2017.
//

#include "TestState.h"
#include "map.h"
#include <iostream>
#include "object.h"
#include "Player.h"
#include "Obstacle.h"

TestState::TestState() {
// Load map information from JSON into object list
    if (!Map::load("Bilder/Stages/TMX/teststage3.json", objects, obstacles))
    {
        std::cout << "Failed to load map data." << std::endl;
    }

    // Do I need to do this? Or is it already created in initialization?
    // Yes. I need to do this. Why doe?
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

    // Move the user, ect.
    player->process();

    for(Obstacle* obs: obstacles) {
        // Weird behaviour when this is while statement instead of if statement
        //std::cout << "collision: " << player->checkCollision(obs) << std::endl;
        while (player->checkCollision(obs)) {
            //std::cout << "time" << std::endl;
            /*
            if(player->getLeftright() == "right"){
                player->move(-1, 0);
            } else{
                player->move(1, 0);
            }
            if(player->getUpdown() == "up"){
                player->move(0, 1);
            } else{
                player->move(0, -1);
            }*/
        }
        //std::cout << "out" << std::endl;
    }
    machine->getWindow().clear(sf::Color::Black);

    // Draw the map
    for (Object* object : objects)
    {
        object->draw(machine->getWindow());
    }

    // Draw the user
    player->draw(machine->getWindow());

    //std::cout << "OBSTACLE SIZE: " << obstacles.size() << std::endl;
    // For testing. Drawing obstacles
    for(Obstacle* obstacle: obstacles)
    {
        //std::cout << "OBSTACLE" << std::endl;
        //machine->getWindow().draw(*obstacle);
        obstacle->draw(machine->getWindow());
    }

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
        // Print Mouse Position
        /*
        player->printPos();
        sf::Vector2f worldPos = machine->getWindow().mapPixelToCoords(sf::Mouse::getPosition(machine->getWindow()));
        std::cout << "Relative Mouse pos" << std::endl << "x: " << worldPos.x << "\ty: " << worldPos.y << std::endl << std::endl;
        std::cout << "Real Mouse pos" << std::endl << "x: " << sf::Mouse::getPosition(machine->getWindow()).x << "\ty: " << sf::Mouse::getPosition(machine->getWindow()).y << std::endl << std::endl;
         */

        // Print Player Position
        /*
        std::cout << std::endl << "Player class pos: " << player->getX() << ", " << player->getY() << std::endl;
        std::cout << "Sprite pos: " << player->getsfSprite().getPosition().x << ", " << player->getsfSprite().getPosition().y << std::endl;
        sf::FloatRect fr = player->getsfSprite().getLocalBounds();
        std::cout << "Player Local bounds pos: " << fr.left << ", " << fr.top << std::endl;
        std::cout << "Player Local bounds size: " << fr.width << ", " << fr.height << std::endl;
        fr = player->getsfSprite().getGlobalBounds();
        std::cout << "Local global pos: " << fr.left << ", " << fr.top << std::endl;
        std::cout << "Local global size: " << fr.width << ", " << fr.height << std::endl;
        */

        // See if mouse collision with player
        sf::Vector2f worldPos = machine->getWindow().mapPixelToCoords(sf::Mouse::getPosition(machine->getWindow()));
        if(player->checkPointCollision(worldPos)){
            std::cout << "hit player" << std::endl;
        }else {
            std::cout << "didnt hit player" << std::endl;
        }
    }
}

void TestState::setMachine(GameMachine *machine) {
    this->machine = machine;
}

void TestState::extrafunc(std::string command) {
    State::extrafunc(command);
}


