
//
// Created by Theo OMNES on 06/10/2023.
//

#include <SDL_image.h>
#include "SDL2/SDL_ttf.h"
#include "components/point/point.h"

#include "components/color/sdl_color.h"
#include "button.h"
#include "log/log_error.h"
#include "log/log_info.h"
#include "sdl_controller.h"
#include "components/button/button_events/button_events.h"

ButtonEvent button_handle_click(SDL_IHM ihm, SDL_Event event, Button button);

ButtonEvent button_handle_hover(SDL_IHM ihm, SDL_Event event, Button button);

void draw_rounded_rect(SDL_Renderer *renderer, SDL_Rect rect, uint8_t radius);

void draw_filled_circle(SDL_Renderer *renderer, int x, int y, int radius);

bool state_can_handle_event(ButtonState state);

ButtonEvent button_handle_aria(SDL_IHM ihm, SDL_Event event, Button button);



Button create_button(const char *id, Point p, ButtonSize size, ButtonCallback callback) {
    char* button_id = malloc(sizeof(char) * strlen(id));
    strcpy((char*)button_id, id);
    Button button = {
            .id = button_id,
            .state = BUTTON_NORMAL,
            .button_rect = (SDL_Rect) {.x = p.x, .y = p.y},
            .border_radius = 0,
            .texture = NULL,
            .texture_rect = button.button_rect,
            .color = button_color(
                    get_color(SDL_WHITE),
                    get_color(SDL_WHITE),
                    get_color(SDL_WHITE)
            ),
            .callback = callback,
            .size = size,
    };

    log_info("button created: %s", button.id);
    return button;
}

Button
create_text_button(const char *id, SDL_IHM ihm, const char *text, Point p, ButtonSize size, ButtonCallback callback) {
    Button button = create_button(id, p, size, callback);

    SDL_Surface *textSurface = TTF_RenderText_Solid(ihm.font, text, get_color(SDL_WHITE));
    if (textSurface == NULL) {
        log_error("TTF_RenderText_Solid Error: %s.", TTF_GetError());
        return button;
    }
    button.texture = SDL_CreateTextureFromSurface(ihm.renderer, textSurface);
    if (button.texture == NULL) {
        log_error("SDL_CreateTextureFromSurface Error: %s.", SDL_GetError());
        return button;
    }
    SDL_FreeSurface(textSurface);

    return size_button(ihm.window, button);
}


Button create_img_button(const char *id, SDL_IHM ihm, const char *img_path, Point p, ButtonSize size,
                         ButtonCallback callback) {
    Button button = create_button(id, p, size, callback);

    log_info("Loading image %s", img_path);
    button.texture = IMG_LoadTexture(ihm.renderer, img_path);
    button.button_rect.w = size.width;
    button.button_rect.h = size.height;
    if(button.texture == NULL) {
        log_error("IMG_LoadTexture Error: %s.", IMG_GetError());
        return button;
    }
    log_info("Image '%s' loaded", img_path);
    return size_button(ihm.window, button);
}

void draw_button(SDL_Renderer *renderer, Button button) {
    if (button.state == BUTTON_HIDEN) return;
    SDL_Color color = get_button_color_to_draw(button);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    if(button.border_radius == 0) SDL_RenderFillRect(renderer, &button.button_rect);
    else draw_rounded_rect(renderer, button.button_rect, button.border_radius);

    SDL_RenderCopy(renderer, button.texture, NULL, &button.texture_rect);
}

void draw_rounded_rect(SDL_Renderer *renderer, SDL_Rect rect, uint8_t radius) {
    int w = rect.w;
    int h = rect.h;
    int r = radius;

    if (r > w / 2) r = w / 2;
    if (r > h / 2) r = h / 2;

    SDL_RenderDrawLine(renderer, rect.x + r, rect.y, rect.x + w - r, rect.y);
    SDL_RenderDrawLine(renderer, rect.x + r, rect.y + h - 1, rect.x + w - r, rect.y + h - 1);
    SDL_RenderDrawLine(renderer, rect.x, rect.y + r, rect.x, rect.y + h - r);
    SDL_RenderDrawLine(renderer, rect.x + w - 1, rect.y + r, rect.x + w - 1, rect.y + h - r);

    draw_filled_circle(renderer, rect.x + r, rect.y + r, r);
    draw_filled_circle(renderer, rect.x + r, rect.y + h - r - 1, r);
    draw_filled_circle(renderer, rect.x + w - r - 1, rect.y + r, r);
    draw_filled_circle(renderer, rect.x + w - r - 1, rect.y + h - r - 1, r);

    SDL_Rect fill_rect = {rect.x + r, rect.y, w - 2 * r, h};
    SDL_RenderFillRect(renderer, &fill_rect);
    fill_rect = (SDL_Rect) {rect.x, rect.y + r, w, h - 2 * r};
    SDL_RenderFillRect(renderer, &fill_rect);
}

// https://stackoverflow.com/a/65745687
void draw_filled_circle(SDL_Renderer *renderer, int x, int y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

Button color_button(ButtonColor color, Button button) {
    button.color = color;
    return button;
}

ButtonEvent button_handle_event(SDL_IHM ihm, SDL_Event event, Button button) {
    switch (event.type) {
        case SDL_MOUSEBUTTONUP: return button_handle_click(ihm, event, button);
        case SDL_MOUSEMOTION: return button_handle_hover(ihm, event, button);
        case SDL_KEYDOWN: return button_handle_aria(ihm, event, button);
        default: return button_event_not_handled(ihm, button);
    }
}

ButtonEvent button_handle_hover(SDL_IHM ihm, SDL_Event event, Button button) {
    if (event.type != SDL_MOUSEMOTION) return button_event_not_handled(ihm, button);

    if(!state_can_handle_event(button.state)) return button_event_not_handled(ihm, button);

    Point mouse_at = {event.button.x, event.button.y};
    if (button_at_point(button, mouse_at)) {
        return button_hovered(ihm, select_button(button));
    } else {
        return button_unhovered(ihm, unselect_button(button));
    }
}

bool state_can_handle_event(ButtonState state) {
    return state != BUTTON_DISABLED && state != BUTTON_HIDEN;
}

ButtonEvent button_handle_click(SDL_IHM ihm, SDL_Event event, Button button) {
    if (event.type != SDL_MOUSEBUTTONUP) return button_event_not_handled(ihm, button);
    if(!state_can_handle_event(button.state)) return button_event_not_handled(ihm, button);
    Point clicked_at = {event.button.x, event.button.y};
    if (!button_at_point(button, clicked_at)) return button_event_not_handled(ihm, button);

    ButtonCallback callback = button.callback;
    if(callback.invoke == NULL) {
        log_info("No callback for button, nothing to do");
        return button_event_not_handled(ihm, button);
    }
    return callback.invoke(ihm, callback.param);
}

bool button_at_point(Button button, Point point) {
    if (button.state == BUTTON_HIDEN) return false;

    return point.x >= button.button_rect.x && point.x <= button.button_rect.x + button.button_rect.w
           && point.y >= button.button_rect.y && point.y <= button.button_rect.y + button.button_rect.h;
}

ButtonColor button_color(SDL_Color background, SDL_Color hover, SDL_Color disabled) {
    ButtonColor color = {
            .background = background,
            .selected = hover,
            .disabled = disabled,
    };
    return color;
}

Button disable_button(Button button) {
    button.state = BUTTON_DISABLED;
    return button;
}

Button enable_button(Button button) {
    if(button.state == BUTTON_DISABLED) button.state = BUTTON_NORMAL;
    return button;
}

Button select_button(Button button) {
    button.state = BUTTON_SELECTED;
    return button;
}

Button unselect_button(Button button) {
    button.state = BUTTON_NORMAL;
    return button;
}

Button border_radius_button(uint8_t radius, Button button) {
    button.border_radius = radius;
    return button;
}

SDL_Color get_button_color_to_draw(Button button) {
    switch (button.state) {
        case BUTTON_NORMAL: return button.color.background;
        case BUTTON_SELECTED: return button.color.selected;
        case BUTTON_DISABLED: return button.color.disabled;
        case BUTTON_HIDEN: return get_color(SDL_TRANSPARENT);
        default: {
            log_error("Unknown button state %d", button.state);
            return button.color.background;
        }
    }
}

ButtonEvent button_handle_aria(SDL_IHM ihm, SDL_Event event, Button button) {
    if(event.key.keysym.sym != SDLK_RETURN || button.state != BUTTON_SELECTED) {
        return button_event_not_handled(ihm, button);
    }
    ButtonCallback callback = button.callback;
    if(callback.invoke == NULL) {
        log_info("No callback for button");
        return button_event_not_handled(ihm, button);
    }
    return callback.invoke(ihm, callback.param);
}