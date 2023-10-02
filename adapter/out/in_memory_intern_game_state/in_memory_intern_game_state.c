
//
// Created by Theo OMNES on 01/10/2023.
//


#include "../../../domain/map/zone/zone.h"

#include "../../../application/port/out/persistence/intern_game_state/game_state.h"
#include "../../../application/port/out/persistence/intern_game_state/set_intern_game_state.h"
#include "../../../application/port/out/persistence/intern_game_state/get_intern_game_state.h"
#include "../../../application/port/out/persistence/intern_game_state/get_map.h"
#include "../../../application/port/out/persistence/intern_game_state/get_current_fight.h"
#include "../../../application/port/out/persistence/intern_game_state/set_player.h"

DoomDepths GAME_STATE = {DOOM_DEPTHS_EMPTY};

DoomDepths set_intern_game_state(DoomDepths game_state) {
    GAME_STATE = game_state;
    return GAME_STATE;
}

DoomDepths get_intern_game_state() {
    return GAME_STATE;
}

Map get_map() {
    return GAME_STATE.map;
}

Map set_current_map(Map map) {
    GAME_STATE.map = map;
    return map;
}

Fight set_current_fight(Fight fight) {
    set_current_fight_in_game(get_intern_game_state(), fight);
    return fight;
}

Fight get_current_fight() {
    return get_current_fight_in_game(get_intern_game_state());
}

Player get_current_player() {
    return get_current_fight().player;
}

Zone get_current_zone() {
    return get_player_current_zone_in_map(get_map());
}

Player set_player(Player player) {
    Fight fight = get_current_fight();
    fight.player = player;
    set_current_fight(fight);
    return player;
}