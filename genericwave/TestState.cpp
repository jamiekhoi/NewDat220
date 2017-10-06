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
    createPickup("multiplier");
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

    sfHealth.setCharacterSize(24);
    sfHealth.setFillColor(sf::Color::White);
    sfHealth.setOutlineColor(sf::Color::Black);
    sfHealth.setOutlineThickness(2);
    sfHealth.setFont(font);

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

    sfInfo.setCharacterSize(24);
    sfInfo.setFillColor(sf::Color::White);
    sfInfo.setOutlineColor(sf::Color::Black);
    sfInfo.setOutlineThickness(2);
    sfInfo.setFont(font);

    sfDeadText.setCharacterSize(120);
    sfDeadText.setFillColor(sf::Color(50,125,100,1));
    sfDeadText.setOutlineColor(sf::Color(255,255,255,1));
    sfDeadText.setOutlineThickness(3);
    sfDeadText.setFont(font);
    sfDeadText.setString("YOU DIED!");

    // Load map information from JSON into object list
    if (!Map::load("Bilder/Stages/TMX/teststage4.json", objects, obstacles, spawnpoints, stores))
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
    checkMultiplier();

    // Create enemy every few seconds
    if(spawnClock.getElapsedTime().asSeconds() > 4){
        createEnemy();
        //std::cout << "enemy" << std::endl;
        spawnClock.restart();
    }

    if(!playerIsDead){
        // Move the user, ect.
        player->process();
    }

    // Continue firing weapon if left mouse is still held
    if(fireheld ){
        if(player->currentWeapon->firemode == "auto"){
            player->currentWeapon->holdFire(bullets);
        }
        if(player->currentWeapon->firemode == "burst"){

        }
    }

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
    if(playerWasHit){
        if(hitSwitch){
            player->draw(machine->getWindow());
            hitSwitch = false;
        }else{
            hitSwitch = true;
        }
    }else{
        player->draw(machine->getWindow());
    }

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
    moveAndDrawBullets();

    // See if player gets a pickup
    checkPlayerPickup();

    // See if enemy attacks player
    checkEnemyPlayerCollsion();


    // See if player is touching a store
    sfInfo.setString("");
    for(auto store: stores){
        if(player->getsfSprite().getGlobalBounds().intersects(store->getGlobalBounds())){
            sfInfo.setString("Press F to buy stuff!");
        }
    }

    // Draw live pickups
    for(auto p: pickups){
        machine->getWindow().draw(*p);
    }

    // Center the view (What the user is shown on screen)
    centerView();

    //Draw HUD info. Helath, points, ammo etc.
    drawHUD();

    // Display the screen
    machine->getWindow().display();

}

void TestState::checkPlayerPickup() {
    // See if player gets a pickup
    for(auto pick = pickups.begin(); pick != pickups.end();){
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
            else if((*pick)->type == "multiplier"){
                // Turn on a score multiplier
                multiplier = 2;
                scoreMultiplierClock.restart();
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
}

void TestState::centerView() const {// Set the view (what the user sees of the game map)
    // Crude. Actually centers around player sprite's upper left corner
    sf::View tempView = machine->getWindow().getView();
    float tempx = player->getX();
    float tempy = player->getY();
    tempView.setCenter(tempx, tempy);
    machine->getWindow().setView(tempView);
}

void TestState::drawHUD() {// Info about the window view
    sf::View tempv = machine->getWindow().getView();
    auto tempcenter = tempv.getCenter();
    auto tempsize = tempv.getSize();

    // Draw wave number
    sfWave.setString("Wave: " + std::__cxx11::to_string(wave));
    sfWave.setPosition(tempcenter.x - tempsize.x / 2 + 50, tempcenter.y - tempsize.y / 2 + 50);
    machine->getWindow().draw(sfWave);

    // Draw points
    sfPoints.setString("Points: " + std::__cxx11::to_string(points));
    sfPoints.setPosition(tempcenter.x + tempsize.x / 2 - 200, tempcenter.y - tempsize.y / 2 + 50);
    machine->getWindow().draw(sfPoints);

    // Draw health
    sfHealth.setString("HP: " + std::__cxx11::to_string(health) + " <3");
    sfHealth.setPosition(tempcenter.x - tempsize.x / 2 + 50, tempcenter.y + tempsize.y / 2 - 100);
    machine->getWindow().draw(sfHealth);

    // Draw weapon name, ammo count and magazine count
    sfWeapon.setString(player->currentWeapon->name);
    sfWeapon.setPosition(tempcenter.x + tempsize.x / 2 - 200, tempcenter.y + tempsize.y / 2 - 100);
    machine->getWindow().draw(sfWeapon);
    sfAmmo.setPosition(tempcenter.x + tempsize.x / 2 - 200, tempcenter.y + tempsize.y / 2 - 50);
    sfAmmo.setString(std::__cxx11::to_string(player->currentWeapon->ammo) + "/" + std::__cxx11::to_string(
            player->currentWeapon->magazines * player->currentWeapon->maxAmmoCount));
    machine->getWindow().draw(sfAmmo);

    // Draw info
    sfInfo.setPosition(tempcenter.x - 100, tempcenter.y);
    machine->getWindow().draw(sfInfo);

    // Draw you died text if player is dead
    if(playerIsDead){
        sfDeadText.setPosition(tempcenter.x - 250, tempcenter.y - 100);
        uint8_t opacity = sfDeadText.getFillColor().a;
        if(opacity < 255){
            sf::Color outlineColor = sfDeadText.getOutlineColor();
            sf::Color fillColor = sfDeadText.getFillColor();
            int changerate = 2;
            if(opacity + changerate >= 255){
                outlineColor.a = 255;
                fillColor.a = 255;
                readyToExit = true;

            } else if(opacity + changerate < 255){
                outlineColor.a += changerate;
                fillColor.a += changerate;
            }
            sfDeadText.setOutlineColor(outlineColor);
            sfDeadText.setFillColor(fillColor);
        }
        machine->getWindow().draw(sfDeadText);
    }

}

void TestState::checkEnemyPlayerCollsion() {// See if enemy attacks player
    if(playerWasHit){
        if(playerHitClock.getElapsedTime().asSeconds() > 1.5){
            playerWasHit = false;
        }
    }else{
        for(Enemy* en: enemies){
            if(en->checkCollisionPlayer(player)){
                health -= 10;
                if(health <= 0){
                    health = 0;
                    playerIsDead = true;
                }
                playerWasHit = true;
                playerHitClock.restart();
                break;
            }
        }
    }
}

void TestState::checkMultiplier() {// Check if score multiplier is active and when to deactivate it
    if(multiplier != 1){
        if(scoreMultiplierClock.getElapsedTime().asSeconds() > 10){
            multiplier = 1;
        }
    }
}

void TestState::moveAndDrawBullets() {
    for(auto bull = bullets.begin(); bull != bullets.end();){

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
                    points += (*en)->points * multiplier;
                    delete (*en);
                    (*en) = nullptr;
                    en = enemies.erase(en);
                    kills++;
                    wave = kills / 2 + 1;

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
        if(readyToExit){
            machine->SetState(GameMachine::StateId::MAINMENU);
        } else if(!playerIsDead){
            if(event.mouseButton.button == sf::Mouse::Left){
                player->fireWeapon(bullets);
                fireheld = true;
            }
        }

    }else if(event.type == sf::Event::MouseButtonReleased){
        if(!playerIsDead){
            if(event.mouseButton.button == sf::Mouse::Left){
                fireheld = false;
            }
        }
    } if(event.type == sf::Event::KeyPressed){

        if(event.key.code == sf::Keyboard::E){
            createEnemy();
        }else if(event.key.code == sf::Keyboard::Num1){
            player->switchWeapon(0);
        }else if(event.key.code == sf::Keyboard::Num2){
            player->switchWeapon(1);
        }else if(event.key.code == sf::Keyboard::Num3){

        }else if(event.key.code == sf::Keyboard::F){
            if(!playerIsDead){
                for(auto store: stores){
                    if(player->getsfSprite().getGlobalBounds().intersects(store->getGlobalBounds())){
                        if(points >= 100){
                            points -= 100;
                            // Give player more ammo
                            player->currentWeapon->magazines = player->currentWeapon->maxMagazineCount;
                            player->currentWeapon->ammo = player->currentWeapon->maxAmmoCount;
                        }
                    }
                }
            }
        }
    }

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
    if(type == "ammo"){
        if (!t->loadFromFile("Bilder/Pickups/Weapons/weapon2pickup.png"))
        {
            std::cout << "Failed to load weapon2pickup texture" << std::endl;
        }
    }else if(type == "multiplier"){
        if (!t->loadFromFile("Bilder/Pickups/Weapons/weapon2pickup.png"))
        {
            std::cout << "Failed to load weapon2pickup texture" << std::endl;
        }
    }
    Pickup* p = new Pickup();
    p->type = type;
    p->bettertexturesetter(t);
    // Should set pickup position to a random spot on the map that doesn't collide with any obstacles
    p->setPosition(500, 500);
    pickups.push_back(p);
}

TestState::~TestState() {

}

TestState::TestState(GameMachine *machine) {
    TestState();
    setMachine(machine);
}


