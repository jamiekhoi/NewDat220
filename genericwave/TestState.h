//
// Created by Jack on 18.06.2017.
//

#ifndef GENERICWAVE_TESTSTATE_H
#define GENERICWAVE_TESTSTATE_H

#include "state.h"
#include <list>

class Player;
class Object;

class TestState: public State {
public:
    TestState();
    void Running();

    // Handles event
    void handleEvent(sf::Event& event);

    void setMachine(GameMachine* machine);
    void extrafunc(std::string command);

protected:
    GameMachine* machine;
    // List of game objects. Should of course be put somewhere else in a bigger game
    std::list<Object*> objects;

    // List of obstacles for hit-test collision
    std::list<sf::RectangleShape*> obstacles;

    sf::Clock clock;

    // Player that the user controls
    Player* player;
};


#endif //GENERICWAVE_TESTSTATE_H
