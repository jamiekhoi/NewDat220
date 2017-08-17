//
// Created by Jack on 23.07.2017.
//

#ifndef GENERICWAVE_PICKUP_H
#define GENERICWAVE_PICKUP_H

#include <string>
#include <SFML/Graphics/Sprite.hpp>

class Pickup: public sf::Sprite{
public:
    Pickup();
    ~Pickup();
    bool bettertexturesetter(sf::Texture* t);
    std::string type;
    sf::Texture* t;

};


#endif //GENERICWAVE_PICKUP_H
