
//
// Created by Theo OMNES on 12/09/2023.
//

#ifndef DOOMDEPTHS_PLAYER_H
#define DOOMDEPTHS_PLAYER_H

#include "stdint.h"
#include "stdbool.h"

#include "grimoire/grimoire.h"
#include "weapon/weapon.h"
#include "inventory/inventory.h"
#include "equipment/equipment.h"

typedef struct Player {
    uint8_t current_health;
    uint8_t max_health;
    uint8_t remaining_number_of_attacks;
    Equipment equipment;
    Grimoire grimoire;
    Inventory inventory;
    uint8_t current_mana;
    uint8_t max_mana;
    bool is_empty;
} Player;

Player player(uint8_t max_health, uint8_t mana);

Player empty_player();

char *player_to_string(Player p);

Player restore_player_number_of_remaining_attacks(Player);

Player player_recover_mana(Player p, uint8_t mana);

bool player_is_dead(Player p);

bool player_is_alive(Player p);

Player free_player(Player p);

bool player_is_empty(Player p);

#endif //DOOMDEPTHS_PLAYER_H
