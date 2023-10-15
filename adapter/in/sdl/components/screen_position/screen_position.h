
//
// Created by Theo OMNES on 15/10/2023.
//

#ifndef DOOMDEPTHS_SCREEN_POSITION_H
#define DOOMDEPTHS_SCREEN_POSITION_H

typedef struct Button Button;

enum position_ {
    NOT_POSITIONED,
    POSITION_START,
    POSITION_END,
    POSITION_CENTER,
};

typedef enum {
    WINDOW,
    PARENT,
} PositionZone;

typedef enum position_ VerticalPosition;
typedef enum position_ HorizontalPosition;

typedef struct {
    PositionZone zone;
    VerticalPosition vertical;
    HorizontalPosition horizontal;
} PositionInScreen;

Button position_button(PositionInScreen position, Button button, SDL_Rect zone);

#endif //DOOMDEPTHS_SCREEN_POSITION_H