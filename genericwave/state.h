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
    virtual void Running() = 0;/*
    virtual void buttonPressed(std::string button) = 0;
    virtual void buttonHeld(std::string button) = 0;
    virtual void mouseClick() = 0;
    virtual void mouseScroll() = 0;*/
    virtual void handleEvent(sf::Event& event) = 0;
    virtual void setMachine(GameMachine* machine) = 0;
    virtual void extrafunc(std::string command){}
};


#endif //GENERICWAVE_STATE_H
