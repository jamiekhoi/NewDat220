//
// Created by Jack on 23.07.2017.
//

#include "Pickup.h"

Pickup::Pickup() {

    sf::Sprite();
}

Pickup::~Pickup() {
    // Build warning here check out later
    delete t;
}

bool Pickup::bettertexturesetter(sf::Texture *t) {
    this->t = t;
    setTexture(*t);
    return true;
}
