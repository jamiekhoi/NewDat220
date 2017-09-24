//
// Created by Jack on 24.09.2017.
//

#ifndef GENERICWAVE_MAINMENUSTATE_H
#define GENERICWAVE_MAINMENUSTATE_H


#include "state.h"

class MainMenuState: public State {
public:
    MainMenuState();
    MainMenuState(GameMachine* machine);
    void Running();
    void handleEvent(sf::Event& event);
    void setMachine(GameMachine* machine);

protected:

};


#endif //GENERICWAVE_MAINMENUSTATE_H
