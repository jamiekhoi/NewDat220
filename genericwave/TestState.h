//
// Created by Jack on 18.06.2017.
//

#ifndef GENERICWAVE_TESTSTATE_H
#define GENERICWAVE_TESTSTATE_H

#include "state.h"
#include "Pickup.h"
#include <list>

class Player;
class Object;
class Obstacle;
class Bullet;
class Enemy;

class TestState: public State {
public:
    TestState();
    TestState(GameMachine* machine);
    ~TestState();
    void Running();

    // Handles event
    void handleEvent(sf::Event& event);
    void extrafunc(std::string command);


protected:

    int maxHealth = 20;
    int health = maxHealth;

    int multiplier = 1;
    int pointsPerEnemy = 50;

    // List of game objects. Should of course be put somewhere else in a bigger game
    std::list<Object*> objects;

    // List of obstacles for hit-test collision
    std::list<Obstacle*> obstacles;

    // List of live bullets
    std::vector<Bullet*> bullets;

    // List of live enemies
    std::vector<Enemy*> enemies;

    // List of doors the player can spend points on to unlock new areas of the map
    //std::vector<

    // List of stores where player can buy ammo and other things
    std::list<Obstacle*> stores;

    // Spawnpoints for the enemy
    std::vector<sf::FloatRect*> spawnpoints;

    // List of live pickups/powerups
    std::vector<Pickup*> pickups;

    // Clocks and timers for automated events
    sf::Clock spawnClock;
    sf::Clock wavePauseClock;
    sf::Clock scoreMultiplierClock;
    sf::Clock playerHitClock;
    //sf::Clock deadClock;

    bool newWavePause = false;
    bool playerWasHit = false;
    bool hitSwitch = false;
    bool playerIsDead = false;
    bool readyToExit = false;

    // Player that the user controls
    Player* player;

    bool fireheld = false;
    int points = 0;
    int kills = 0;
    int wave = 1;

    sf::Text sfInfo;
    sf::Text sfWave;
    sf::Text sfPoints;
    sf::Text sfHealth;
    sf::Text sfAmmo;
    sf::Text sfMagazines;
    sf::Text sfWeapon;
    sf::Text sfDeadText;
    sf::Font font;

    void createEnemy();
    void createPickup();
    void createPickup(std::string type);

    void moveAndDrawBullets();

    void checkMultiplier();

    void checkEnemyPlayerCollsion();

    void drawHUD();

    void centerView() const;

    void checkPlayerPickup();
};


#endif //GENERICWAVE_TESTSTATE_H
