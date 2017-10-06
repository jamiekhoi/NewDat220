//
// Created by Jack on 24.09.2017.
//

#include <iostream>
#include "MainMenuState.h"

MainMenuState::MainMenuState() {
    if (!font.loadFromFile("Font/Montserrat-Regular.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
    }
    sfPlay.setCharacterSize(40);
    sfPlay.setFillColor(sf::Color::White);
    sfPlay.setOutlineColor(sf::Color::Black);
    sfPlay.setOutlineThickness(2);
    sfPlay.setString("Play game");
    sfPlay.setFont(font);
    sfPlay.setPosition(200, 200);
}

void MainMenuState::Running() {
    machine->getWindow().clear(sf::Color::Blue);
    machine->getWindow().draw(sfPlay);
    machine->getWindow().display();
}

void MainMenuState::handleEvent(sf::Event &event) {
    if(event.type == sf::Event::MouseButtonReleased){
        std::cout << "click" << std::endl;
        if(sfPlay.getGlobalBounds().contains(machine->getWindow().mapPixelToCoords(sf::Mouse::getPosition(machine->getWindow())))){
            std::cout << "click play" << std::endl;
            machine->SetState(GameMachine::StateId::RUNNING);
        }
    }
}

MainMenuState::MainMenuState(GameMachine *machine) {

}
