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

    // Check player-obstacle collision
    for(Obstacle* obs: obstacles) {

        // Everything is handled inside player->checkCollision()
        while (player->checkCollision(obs)) {}

    }

    // Clear screen
    machine->getWindow().clear(sf::Color::Black);

    // Draw the map
    for (Object* object : objects)
    {
        object->draw(machine->getWindow());
    }

    // Draw the player
    player->draw(machine->getWindow());

    // For testing. Drawing obstacles
    for(Obstacle* obstacle: obstacles)
    {
        //machine->getWindow().draw(*obstacle);
        obstacle->draw(machine->getWindow());
    }

    // Move and draw bullets
    for( std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end();){

        (*it)->move();

        // Loop through obstacle objects
        for(Obstacle* obs: obstacles) {

            if(*it == nullptr){
                break;
            }
            // Check collision with wall. Everything is handled inside bullet
            if ((*it)->checkCollisionObs(obs)) {
                // If hit a wall check bullet penetration level and delete if bullet cannot penetrate further
                if ((*it)->hit()){
                    // Is this correct?
                    delete (*it);
                    (*it) = nullptr;

                    it = bullets.erase(it);

                }

            }

        }

        if((*it) != nullptr){
            (*it)->draw(machine->getWindow());
            it++;
        }
    }
    /*
    for(Bullet* bullet: bullets){
        bullet->move();
        bullet->draw(machine->getWindow());
    }*/

    // Test bullet-enemy collision


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
        /*
        sf::Vector2f worldPos = machine->getWindow().mapPixelToCoords(sf::Mouse::getPosition(machine->getWindow()));
        if(player->checkPointCollision(worldPos)){
            std::cout << "hit player" << std::endl;
        }else {
            std::cout << "didnt hit player" << std::endl;
        }
         */
        player->fireWeapon(bullets);
    }
}

void TestState::setMachine(GameMachine *machine) {
    this->machine = machine;
}

void TestState::extrafunc(std::string command) {
    State::extrafunc(command);
}


