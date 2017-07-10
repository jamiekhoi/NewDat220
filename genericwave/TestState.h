//
// Created by Jack on 18.06.2017.
//

#ifndef GENERICWAVE_TESTSTATE_H
#define GENERICWAVE_TESTSTATE_H

#include "state.h"
#include <list>

class Player;
class Object;
class Obstacle;
class Bullet;
class Enemy;

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
    std::list<Obstacle*> obstacles;

    // List of live bullets
    std::vector<Bullet*> bullets;

    // List of live enemies
    std::vector<Enemy*> enemies;

    // Spawnpoints for the enemy
    std::vector<sf::FloatRect*> spawnpoints;

    sf::Clock clock;

    // Player that the user controls
    Player* player;

    int points = 0;

    int wave = 1;

    sf::Text sfWave;
    sf::Text sfPoints;
    sf::Text sfHealth;
    sf::Text sfAmmo;
    sf::Text sfWeapon;
    sf::Font font;

    void createEnemy();
};


#endif //GENERICWAVE_TESTSTATE_H
