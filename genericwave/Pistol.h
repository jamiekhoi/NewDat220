//
// Created by Jack on 21.06.2017.
//

#ifndef GENERICWAVE_PISTOL_H
#define GENERICWAVE_PISTOL_H

#include "Weapon.h"

class Pistol: public Weapon {
public:
    Pistol();
    void fire();
    void reload();
    void addAmmo();
};


#endif //GENERICWAVE_PISTOL_H
