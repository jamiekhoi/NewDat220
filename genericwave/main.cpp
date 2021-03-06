#include <iostream>
#include "gamemachine.h"
#include "TestState.h"
#include "MainMenuState.h"

int main() {
    /*
     * NB!!!!
     * Random crash sometimes with obstacle collision
     *
     * Main todo:
     * when player dies and returns to main menu, need to reset the view or play button may appear offscreen
     *
     * Need to create bounds for the game
     * Should view control be in gamemachine.cpp or in each state???
     * fix no image when player colliding with obstacle
     * Switch animation direction to enum?
     * Bullet exit angle off. Perhaps angle not accurate enough? Change to double?
     * Headshots more damage
     *
     * Change Obstacle class in release.
     * Minor memory leaks?
     * Check for memory leak in pistol.cpp constructor when creating new bullettexture pointer.
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
     * Should reloading weapon take time?
     *
     * If game is slowing down change pickup creating/deletion
     *
     * Make bullet contain list of enemies it has hit, so that it only hits each enemy once
     *
     * Make player texture loading dynamic, based on image size, not hardcoded
     */

    GameMachine* WaveShooter = new GameMachine();

    //Set running flag to true
    WaveShooter->SetRunning(true);

    // Create states
    TestState* teststate = new TestState();
    MainMenuState* mainmenustate = new MainMenuState();

    // Add machine access to states // Why couldn't I do this in the constructor???
    teststate->setMachine(WaveShooter);
    mainmenustate->setMachine(WaveShooter);

    // Add states
    WaveShooter->AddState(teststate);
    WaveShooter->AddState(mainmenustate);

    // Set current state
    WaveShooter->SetState(0);

    // Run until the running flag is set to false
    while (WaveShooter->GetRunning()){
        WaveShooter->Run();
    }

    return 0;
}