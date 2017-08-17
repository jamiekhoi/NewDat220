//
// Created by Jack on 18.06.2017.
//

#include "TestState.h"
#include "map.h"
#include <iostream>
#include "object.h"
#include "Player.h"
#include "Obstacle.h"
#include "Enemy.h"

TestState::TestState() {

    if (!font.loadFromFile("Font/Montserrat-Regular.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
    }
    sfWave.setCharacterSize(24);
    sfWave.setFillColor(sf::Color::White);
    sfWave.setOutlineColor(sf::Color::Black);
    sfWave.setOutlineThickness(2);
    //sfWave.setString("Wave " + std::to_string(wave));
    sfWave.setFont(font);

    sfPoints.setCharacterSize(24);
    sfPoints.setFillColor(sf::Color::White);
    sfPoints.setOutlineColor(sf::Color::Black);
    sfPoints.setOutlineThickness(2);
    //sfPoints.setString("Points: " + std::to_string(wave));
    sfPoints.setFont(font);

    sfWeapon.setCharacterSize(24);
    sfWeapon.setFillColor(sf::Color::White);
    sfWeapon.setOutlineColor(sf::Color::Black);
    sfWeapon.setOutlineThickness(2);
    sfWeapon.setFont(font);

    sfAmmo.setCharacterSize(24);
    sfAmmo.setFillColor(sf::Color::White);
    sfAmmo.setOutlineColor(sf::Color::Black);
    sfAmmo.setOutlineThickness(2);
    sfAmmo.setFont(font);

    // Load map information from JSON into object list
    if (!Map::load("Bilder/Stages/TMX/teststage3.json", objects, obstacles, spawnpoints))
    {
        std::cout << "Failed to load map data." << std::endl;
    }
    player = new Player();

    /*
    // Double the size of the screen
    sf::View view = window.getDefaultView();
    view.setSize(view.getSize().x / 2, view.getSize().y / 2);
    view.setCenter(view.getCenter().x / 2, view.getCenter().y / 2);
    window.setView(view);
     */
}

void TestState::Running() {

    // Create enemy every few seconds
    if(clock.getElapsedTime().asMilliseconds() > 4000){
        createEnemy();
        //std::cout << "enemy" << std::endl;
        clock.restart();
    }

    // Move the user, ect.
    player->process();

    // Check player-obstacle collision
    for(Obstacle* obs: obstacles) {

        // Everything is handled inside player->checkCollision()
        while (player->checkCollision(obs)) {}

        for(Enemy * en: enemies){
            while (en->checkCollisionObs(obs)){}
        }
    }

    // Clear screen
    machine->getWindow().clear(sf::Color::Black);

    // Draw the map
    for (Object* object : objects)
    {
        object->draw(machine->getWindow());
    }

    // Draw the player
    player->draw(machine->getWindow());

    // For testing. Drawing obstacles
    for(Obstacle* obstacle: obstacles)
    {
        //machine->getWindow().draw(*obstacle);
        obstacle->draw(machine->getWindow());
    }

    // Move enemies
    // Draw enemies
    for(Enemy* en: enemies){
        en->move(player->getPosition());
        en->draw(machine->getWindow());
    }

    // Move and draw bullets. Also bullet collision test
    for( std::vector<Bullet*>::iterator bull = bullets.begin(); bull != bullets.end();){

        (*bull)->move();

        // Loop through enemies
        for(auto en = enemies.begin(); en != enemies.end();){
            // Do I need this????
            if(*en == nullptr){
                break;
            }
            // Check collision with enemy
            if((*bull)->checkCollisionEnemy((*en))){

                // Decrease enemy health and check if enemie is dead
                if((*en)->dead((*bull)->getDamage())){
                    points += (*en)->points;
                    delete (*en);
                    (*en) = nullptr;
                    en = enemies.erase(en);
                    kills++;
                    wave = kills/2 + 1;

                    // Check how many kills and create a pickup for new weapon if needed
                    if(kills == 2){
                        createPickup("ammo");
                    }
                }

                // Check bullet penetration
                if ((*bull)->hit()){
                    // Is this correct?
                    delete (*bull);
                    (*bull) = nullptr;
                    bull = bullets.erase(bull);
                    break;
                }

            }else{
                en++;
            }
        }

        if((*bull) != nullptr){
            // Loop through obstacle objects
            for(Obstacle* obs: obstacles) {
                // Check collision with wall. Everything is handled inside bullet
                if ((*bull)->checkCollisionObs(obs)) {
                    // If hit a wall check bullet penetration level and delete if bullet cannot penetrate further
                    if ((*bull)->hit()){
                        // Is this correct?
                        delete (*bull);
                        (*bull) = nullptr;
                        bull = bullets.erase(bull);
                        break;
                    }
                }
            }
        }

        if((*bull) != nullptr){
            (*bull)->draw(machine->getWindow());
            bull++;
        }
    }

    // See if player gets a pickup
    for( std::vector<Pickup*>::iterator pick = pickups.begin(); pick != pickups.end();){
        bool s = player->getsfSprite().getGlobalBounds().intersects((*pick)->getGlobalBounds());
        if(player->getsfSprite().getGlobalBounds().intersects((*pick)->getGlobalBounds())){
            // Check what type of pickup
            if((*pick)->type == "ammo"){
                // Give player more ammo
                player->currentWeapon->magazines += 5;
                if (player->currentWeapon->magazines > player->currentWeapon->maxMagazineCount){
                    player->currentWeapon->magazines = player->currentWeapon->maxMagazineCount;
                }
                if(player->currentWeapon->ammo == 0){
                    player->currentWeapon->reload();
                }
            }
            else if((*pick)->type == "doublepoints"){
                // Turn on a score multiplier

            }
            else if((*pick)->type == "weapon2"){
                // Give player new weapon

            }

            // Delete the pickup
            delete (*pick);
            (*pick) = nullptr;
            pick = pickups.erase(pick);
            break;

        }else{
            pick++;
        }
    }

    // Draw live pickups
    for(auto p: pickups){
        machine->getWindow().draw(*p);
    }


    // Set the view (what the user sees of the game map)
    // Crude. Actually centers around player sprite's upper left corner
    sf::View tempView = machine->getWindow().getView();
    float tempx = player->getX();
    float tempy = player->getY();
    tempView.setCenter(tempx, tempy);
    machine->getWindow().setView(tempView);

    // Info about the window view
    sf::View tempv = machine->getWindow().getView();
    auto tempcenter = tempv.getCenter();
    auto tempsize = tempv.getSize();

    // Draw wave number
    sfWave.setString("Wave: " + std::to_string(wave));
    sfWave.setPosition(tempcenter.x - tempsize.x/2 + 50, tempcenter.y - tempsize.y/2 + 50);
    machine->getWindow().draw(sfWave);

    // Draw points
    sfPoints.setString("Points: " + std::to_string(points));
    sfPoints.setPosition(tempcenter.x + tempsize.x/2 - 200, tempcenter.y - tempsize.y/2 + 50);
    machine->getWindow().draw(sfPoints);

    // Draw health


    // Draw weapon name, ammo count and magazine count
    sfWeapon.setString(player->currentWeapon->name);
    sfWeapon.setPosition(tempcenter.x + tempsize.x/2 - 200, tempcenter.y + tempsize.y/2 - 100);
    machine->getWindow().draw(sfWeapon);

    sfAmmo.setString(std::to_string(player->currentWeapon->ammo) + "/" + std::to_string(player->currentWeapon->magazines));
    sfAmmo.setPosition(tempcenter.x + tempsize.x/2 - 200, tempcenter.y + tempsize.y/2 - 50);
    machine->getWindow().draw(sfAmmo);

    // Draw the screen
    machine->getWindow().display();

}

void TestState::handleEvent(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed)
    {
        // Print Mouse Position
        /*
        player->printPos();
        sf::Vector2f worldPos = machine->getWindow().mapPixelToCoords(sf::Mouse::getPosition(machine->getWindow()));
        std::cout << "Relative Mouse pos" << std::endl << "x: " << worldPos.x << "\ty: " << worldPos.y << std::endl << std::endl;
        std::cout << "Real Mouse pos" << std::endl << "x: " << sf::Mouse::getPosition(machine->getWindow()).x << "\ty: " << sf::Mouse::getPosition(machine->getWindow()).y << std::endl << std::endl;
         */

        // Print Player Position
        /*
        std::cout << std::endl << "Player class pos: " << player->getX() << ", " << player->getY() << std::endl;
        std::cout << "Sprite pos: " << player->getsfSprite().getPosition().x << ", " << player->getsfSprite().getPosition().y << std::endl;
        sf::FloatRect fr = player->getsfSprite().getLocalBounds();
        std::cout << "Player Local bounds pos: " << fr.left << ", " << fr.top << std::endl;
        std::cout << "Player Local bounds size: " << fr.width << ", " << fr.height << std::endl;
        fr = player->getsfSprite().getGlobalBounds();
        std::cout << "Local global pos: " << fr.left << ", " << fr.top << std::endl;
        std::cout << "Local global size: " << fr.width << ", " << fr.height << std::endl;
        */

        // See if mouse collision with player
        /*
        sf::Vector2f worldPos = machine->getWindow().mapPixelToCoords(sf::Mouse::getPosition(machine->getWindow()));
        if(player->checkPointCollision(worldPos)){
            std::cout << "hit player" << std::endl;
        }else {
            std::cout << "didnt hit player" << std::endl;
        }
         */
        player->fireWeapon(bullets);
    }else if(event.type == sf::Event::KeyPressed){

        if(event.key.code == sf::Keyboard::E){
            createEnemy();
        }
    }

}

void TestState::setMachine(GameMachine *machine) {
    this->machine = machine;
}

void TestState::extrafunc(std::string command) {
    State::extrafunc(command);
}

void TestState::createEnemy() {
    // Create enemy
    Enemy* en = new Enemy();

    // Create a hitbox for the screen
    sf::View tempv = machine->getWindow().getView();
    auto tempcenter = tempv.getCenter();
    auto tempsize = tempv.getSize();
    float xpos = tempcenter.x - tempsize.x/2;
    float ypos = tempcenter.y - tempsize.y/2;
    sf::FloatRect viewhitbox = sf::FloatRect(xpos, ypos, tempsize.x, tempsize.y);

    std::vector<sf::FloatRect*> validspawns;
    // Check for spawn points not in the view
    for(sf::FloatRect* spawn: spawnpoints){
        if(!spawn->intersects(viewhitbox)){
            validspawns.push_back(spawn);
        }
    }

    int num = rand()%validspawns.size();
    sf::FloatRect* spa = validspawns[num];

    // Should fix this later
    int enx = rand()%(int)spa->width;
    int eny = rand()%(int)spa->height;

    en->setPosition(spa->left + enx, spa->top + eny);

    // Testing
    // en->setPosition(350, 350);

    enemies.push_back(en);
}

void TestState::createPickup() {
    sf::Texture* t = new sf::Texture();
    if (!t->loadFromFile("Bilder/Pickups/Weapons/weapon2pickup.png"))
    {
        std::cout << "Failed to load weapon2pickup texture" << std::endl;
    }
    Pickup* p = new Pickup();
    p->type = "weapon2";
    p->bettertexturesetter(t);
    // Should set pickup position to a random spot on the map that doesn't collide with any obstacles
    p->setPosition(500, 500);
    pickups.push_back(p);
}

void TestState::createPickup(std::string type) {
    sf::Texture* t = new sf::Texture();
    if (!t->loadFromFile("Bilder/Pickups/Weapons/weapon2pickup.png"))
    {
        std::cout << "Failed to load weapon2pickup texture" << std::endl;
    }
    Pickup* p = new Pickup();
    p->type = type;
    p->bettertexturesetter(t);
    // Should set pickup position to a random spot on the map that doesn't collide with any obstacles
    p->setPosition(500, 500);
    pickups.push_back(p);
}


