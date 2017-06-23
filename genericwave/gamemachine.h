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

    // Window ratio
    float windowRatio = 2.125;

    //1920x1080 1280x720
    //1700/800 = 2.125 (i.e. width = height*2.125)
    int windowHeight = 800;
    int windowWidth = 1700;
    int lowResWindowHeight = 580;
    float lowResWindowWidth = 1232.5;

    int viewCenterX = 0;
    int viewCenterY = 0;

    //width/height = 2.125 (or same ratio as window)
    int viewWidth = 1700;
    int viewHeight = 800;

};


#endif //GENERICWAVE_GAMEMACHINE_H
