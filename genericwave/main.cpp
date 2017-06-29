#include <iostream>
#include "gamemachine.h"
#include "TestState.h"

int main() {
    /*
     * Need to create bounds for the game
     * collision test for objects
     * Should view control be in gamemachine.cpp or in each state???
     * fixed no image when player colliding with obstacle
     *
     * Change Obstacle class in release.
     * Major memory leaks
     * Create de-constructors for classes
     * Operation overload for <<. How to do this?
     *
     * Create an auto aim function cheat
     * sf::Mouse::setPosition to enemy position.
     * Create a sf::rect between player and enemy and check for obstacle collision
     *
     * Use Dijkstra's algorithm for enemy AI, using points on map
     *
     * Round obstacles for rebound shots
     *
     */
    std::cout << "Hello, World!" << std::endl;

    GameMachine* WaveShooter = new GameMachine();

    //Set running flag to true
    WaveShooter->SetRunning(true);

    // Create states
    TestState* teststate = new TestState();

    // Add machine access to states // Why couldn't I do this in the constructor???
    teststate->setMachine(WaveShooter);

    // Add states
    WaveShooter->AddState(teststate);

    // Set current state
    WaveShooter->SetState(0);

    // Run until the running flag is set to false
    while (WaveShooter->GetRunning()){
        WaveShooter->Run();
    }

    return 0;
}