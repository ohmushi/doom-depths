
//
// Created by Theo OMNES on 06/10/2023.
//

#ifndef DOOMDEPTHS_BUTTON_H
#define DOOMDEPTHS_BUTTON_H

#include "SDL2/SDL.h"
#include "in/sdl/components/padding/padding.h"
#include "stdbool.h"

typedef struct SDL_IHM SDL_IHM;
typedef struct Point Point;

typedef struct Button Button;
struct Button{
    bool is_visible;
    SDL_Rect rect;
    SDL_Texture* text_texture;
    SDL_Color bg_color;
    Padding padding;
    void (*callback)();
};

void drawButton(SDL_Renderer *renderer, Button button);

Button padding_button(Padding padding, Button button);

Button create_button(SDL_IHM ihm, const char *text, Point p, void (*callback)());

Button background_color_button(SDL_Color color, Button button);

void button_handle_event(SDL_Event event, Button button);

bool button_is_clicked_at_point(Button button, Point clicked_at);

#endif //DOOMDEPTHS_BUTTON_H