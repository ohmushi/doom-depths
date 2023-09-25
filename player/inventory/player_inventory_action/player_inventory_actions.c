
//
// Created by Theo OMNES on 25/09/2023.
//

#include "player_inventory_actions.h"

const char* inventory_action_to_string(PlayerInventoryAction action) {
    switch (action) {
        case EXIT_INVENTORY: return "Exit inventory";
        case EQUIP_ITEM: return "Equip an item";
        default: return "?";
    }
}