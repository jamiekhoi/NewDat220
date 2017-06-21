//
// Created by Jack on 21.06.2017.
//

#ifndef GENERICWAVE_WEAPON_H
#define GENERICWAVE_WEAPON_H


class Weapon {
public:
    Weapon(){}
    virtual void fire(){}
    virtual void reload(){}
    virtual void addAmmo(){}
};


#endif //GENERICWAVE_WEAPON_H
