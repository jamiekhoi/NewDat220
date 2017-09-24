//
// Created by Jack on 18.06.2017.
//

#ifndef GENERICWAVE_STATE_H
#define GENERICWAVE_STATE_H

#include <string>
#include "SFML/Graphics.hpp"
#include "gamemachine.h"

class GameMachine;

class State {
public:
    State(){}
    virtual void Running() = 0;
    virtual void handleEvent(sf::Event& event) = 0;
    virtual void setMachine(GameMachine* machine){
        this->machine = machine;
    }
    virtual void extrafunc(std::string command){}

protected:
    GameMachine* machine;
};


#endif //GENERICWAVE_STATE_H
