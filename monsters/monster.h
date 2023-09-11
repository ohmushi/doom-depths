
//
// Created by Theo OMNES on 11/09/2023.
//

#ifndef DOOMDEPTHS_MONSTER_H
#define DOOMDEPTHS_MONSTER_H

#include "stdint.h"

typedef struct Monster {
    int8_t hp;
    int8_t min_attack_power;
    int8_t max_attack_power;
    int8_t defense;
} Monster;

#endif //DOOMDEPTHS_MONSTER_H
