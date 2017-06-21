//
// Created by Jack on 18.06.2017.
//

#ifndef GENERICWAVE_GAMEMACHINE_H
#define GENERICWAVE_GAMEMACHINE_H

#include "state.h"

class State;

class GameMachine {
public:
    GameMachine();

    enum class StateId {RUNNING, MAINMENU, singlePlay, settingMenu, highScore, controls};

    void AddState(State* s);
    void Run();
    void SetState(StateId state);
    void SetState(int index);
    void SetRunning(bool running) { this->running = running; }
    bool GetRunning() const { return running; }

    sf::RenderWindow &getWindow() { return window; }


protected:
    bool running = true;
    State* currentState;
    std::vector<State*> states;
    sf::RenderWindow window;
    //int windowheight = 1080;
    //int windowwidth = 1920;
    int windowheight = 720;
    int windowwidth = 1280;

};


#endif //GENERICWAVE_GAMEMACHINE_H
