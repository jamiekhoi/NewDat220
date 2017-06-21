//
// Created by Jack on 18.06.2017.
//

#include "gamemachine.h"

GameMachine::GameMachine() {
    window.create(sf::VideoMode(windowwidth, windowheight), "Zombie Wave Annihilation");
    window.setVerticalSyncEnabled(true);
    // Set framerate limit. Otherwise game speed would be dependent on cpu speed.
    window.setFramerateLimit(60);
    // Disables a keypress held resulting in multiple presses
    window.setKeyRepeatEnabled(false);
}

void GameMachine::AddState(State *s) {
    states.push_back(s);
}

void GameMachine::Run() {

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            running = false;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {

        }else {
            currentState->handleEvent(event);
        }
    }

    // Should this wbe inside the while loop?
    currentState->Running();
}

void GameMachine::SetState(GameMachine::StateId state) {
    currentState = states[(std::size_t)state];
}

void GameMachine::SetState(int index) {
    currentState = states[index];
}
