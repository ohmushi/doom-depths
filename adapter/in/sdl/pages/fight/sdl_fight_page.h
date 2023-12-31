
//
// Created by Theo OMNES on 13/10/2023.
//

#ifndef DOOMDEPTHS_SDL_FIGHT_PAGE_H
#define DOOMDEPTHS_SDL_FIGHT_PAGE_H

#include <SDL_render.h>
#include <SDL_events.h>
#include "pages/fight/health_bar/health_bar.h"
#include "components/row/row.h"
#include "pages/fight/sdl_player/sdl_player.h"
#include "fight.h"
#include "pages/fight/sdl_monsters/sdl_monster.h"

typedef struct SDL_IHM SDL_IHM;

typedef struct  {
    SdlPlayer player;
    SdlMonsters monsters;
    Fight fight;
    Row buttons;
} FightPage;

FightPage fill_fight_page(SDL_IHM ihm);

void draw_fight_page(SDL_Renderer *renderer, FightPage fight_page, SDL_IHM ihm);

SDL_IHM fight_page_handle_event(SDL_Event event, SDL_IHM ihm);

SDL_IHM update_fight_page(SDL_IHM ihm);

FightPage update_state_of_fight_page(FightPage fight);

#endif //DOOMDEPTHS_SDL_FIGHT_PAGE_H
