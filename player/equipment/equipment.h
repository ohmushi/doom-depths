
//
// Created by Theo OMNES on 25/09/2023.
//

#ifndef DOOMDEPTHS_EQUIPMENT_H
#define DOOMDEPTHS_EQUIPMENT_H

#include "../../fight/weapon/weapon.h"

typedef struct Equipment {
    Weapon weapon;
} Equipment;

Equipment default_equipment();
char* equipment_to_string(Equipment e);

#endif //DOOMDEPTHS_EQUIPMENT_H