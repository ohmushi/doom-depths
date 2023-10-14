
//
// Created by Theo OMNES on 13/10/2023.
//

#include <SDL_image.h>
#include "in/sdl/sdl_controller.h"
#include "sdl_fight_page.h"
#include "port/out/log/log_error.h"
#include "port/out/persistence/intern_game_state/get_player.h"

void draw_player(SDL_Renderer *renderer, SdlPlayer player, SDL_IHM ihm);

FightPage fill_fight_page(SDL_IHM ihm) {
    FightPage fight = ihm.page.fight;
    fight.player.texture = IMG_LoadTexture(ihm.renderer, "resources/assets/player.png");
    if(fight.player.texture == NULL) {
        log_error("IMG_LoadTexture Error: %s.", IMG_GetError());
        return fight;
    }

    fight.player.source_sprites_rect = (SDL_Rect){
            .w = 32,
            .h = 32,
            .x = 0,
            .y = 0,
    };

    int size = 32;
    fight.player.destination_sprite_rect = (SDL_Rect){
            .w = size * 5,
            .h = size * 5,
            .x = 10,
            .y = 100,
    };
    fight.player.current_sprite = 0;

    fight.player.player = get_player();
    fight.player.health_bar = (HealthBar){
            .health_color = get_color(SDL_GREEN),
            .max_health = fight.player.player.max_health,
            .current_health = fight.player.player.max_health,
    };
    return fight;
}

void draw_fight_page(SDL_Renderer *renderer, FightPage fight_page, SDL_IHM ihm) {
    draw_player(renderer, fight_page.player, ihm);
    // draw buttons for actions (attack, defend, open grimoire, end turn)
    // draw enemy and its health bar

}

void draw_player(SDL_Renderer *renderer, SdlPlayer player, SDL_IHM ihm) {
    player.source_sprites_rect.x = 32 * ((player.current_sprite / 12) % 10);
    SDL_RenderCopy(renderer, player.texture, &player.source_sprites_rect, &player.destination_sprite_rect);
    player.health_bar.current_health = player.player.current_health;
    player.health_bar.rect = (SDL_Rect){
            .w = player.destination_sprite_rect.w,
            .h = 15,
            .x = player.destination_sprite_rect.x,
            .y = player.destination_sprite_rect.y - 20,
    };
    draw_health_bar(renderer, player.health_bar, ihm.font);
}

SDL_IHM fight_page_handle_event(SDL_Event event, SDL_IHM ihm) {
    // TODO
    return ihm;
}

SDL_IHM update_fight_page(SDL_IHM ihm) {
    ihm.page.fight.player.current_sprite += 1;
    if(ihm.page.fight.player.current_sprite > 1000 ) ihm.page.fight.player.current_sprite = 0;
    return ihm;
}