//
// Created by Jack on 18.06.2017.
//

#include "gamemachine.h"
#include <iostream>

GameMachine::GameMachine() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Get screen resolution
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();

    if(videoMode.width > 1800 && videoMode.height > 980){
        window.create(sf::VideoMode(windowWidth, windowHeight), "Zombie Wave Annihilation", sf::Style::Default, settings);
    }else{
        window.create(sf::VideoMode(lowResWindowWidth, lowResWindowHeight), "Zombie Wave Annihilation", sf::Style::Default, settings);
    }

    // Set framerate limit. Otherwise game speed would be dependent on cpu speed.
    window.setFramerateLimit(frameRateLimit);

    // Vertical sync limits framerate differently for differnt computers. WHY???
    //window.setVerticalSyncEnabled(true);

    // Disables a keypress held resulting in multiple presses
    window.setKeyRepeatEnabled(false);

    sf::View view1 = window.getDefaultView();
    //view1.setSize(640, 360);
    //view1.setCenter(640, 360);
    view1.setSize(viewWidth, viewHeight);
    view1.setCenter(viewCenterX, viewCenterY);
    view1.zoom(1);
    window.setView(view1);
}

void GameMachine::AddState(State *s) {
    states.push_back(s);
}

void GameMachine::Run() {

    sf::Event event;
    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::GainedFocus){
            inFocus = true;
        } else if (event.type == sf::Event::LostFocus){
            inFocus = false;
        }

        if(!inFocus){
            continue;
        }

        if (event.type == sf::Event::Closed)
        {
            window.close();
            running = false;
        }
        /*else if (event.type == sf::Event::MouseButtonPressed)
        {
            player.printPos();
            std::cout << "Mouse pos" << std::endl << "x: " << sf::Mouse::getPosition().x << "\ty: " << sf::Mouse::getPosition().y << std::endl;
        }*/
        else if (event.type == sf::Event::KeyPressed)
        {
            // Test if this results in multple key presses if button is help on another computer
            if (event.key.code == sf::Keyboard::R){
                std::cout << sf::VideoMode::getDesktopMode().height << ", w:" << sf::VideoMode::getDesktopMode().width << std::endl;
            }else{
                currentState->handleEvent(event);
            }
        }
        else if (event.type == sf::Event::Resized)
        {
            int tempheight = window.getSize().y;
            // 0.5625 is  window height/width
            window.setSize(sf::Vector2u(tempheight*windowRatio, tempheight));
            //window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
        }
        else {
            currentState->handleEvent(event);
        }
    }

    // Should this wbe inside the while loop? No
    if(inFocus){
        currentState->Running();
    }
}

void GameMachine::SetState(GameMachine::StateId state) {
    currentState = states[(std::size_t)state];
}

void GameMachine::SetState(int index) {
    currentState = states[index];
}
