
//
// Created by Theo OMNES on 01/10/2023.
//

#include <string.h>

#include <port/in/command/drink_potion.h>

#include <player.h>

#include "log/log_error.h"
#include "log/log_info.h"
#include <port/out/persistence/intern_game_state/set_player.h>
#include <port/out/persistence/intern_game_state/get_player.h>

void drink_potion_at_index(uint8_t potion_index) {
    Player player = get_player();
    if (potion_index < 0 || potion_index >= player.inventory.capacity) {
        log_error("Index [%d] is not in inventory", potion_index);
        return;
    }

    if (player.inventory.items[potion_index].type != POTION_ITEM) {
        log_error("Item at index [%d] is not a potion", potion_index);
        return;
    }

    InventoryItem potion_item = player.inventory.items[potion_index];
    ManaPotion mana_potion = *((ManaPotion *) potion_item.item);
    if (mana_potion.is_full) {
        player = player_recover_mana(player, player.max_mana);
    } else {
        log_info("Potion is empty.");
    }

    player.inventory.items[potion_index] = empty_inventory_item();
    free(potion_item.item);
    potion_item.item = NULL;

    set_player(player);
}