#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>


//change pointer's x and y

bool first_menu_move_pointer(int *pointer_x, int *pointer_y) {

    Uint8 *keystates2 = SDL_GetKeyState(NULL);
    SDL_Event first_menu_pointer_move;
    if (SDL_PollEvent(&first_menu_pointer_move)) {
        if (keystates2[SDLK_DOWN]) {
            if (*pointer_y != 925 && *pointer_x == 40) {
                *pointer_y += 125;
            }
            if (*pointer_y == 775 && *pointer_x == 640) {
                *pointer_x = 800;
                *pointer_y = 925;
            }
            if (*pointer_y == 650 && *pointer_x == 640) {
                *pointer_x = 640;
                *pointer_y = 775;
            }
        }
        if (keystates2[SDLK_UP]) {
            if (*pointer_y != 650 && *pointer_x == 40) {
                *pointer_y -= 125;
            }
            if (*pointer_y == 775 && *pointer_x == 640) {
                *pointer_y = 650;
            }
            if (*pointer_y == 925 && *pointer_x == 800) {
                *pointer_x = 640;
                *pointer_y = 775;
            }
        }
        if (keystates2[SDLK_RIGHT]) {
            if (*pointer_y != 900) {
                *pointer_x = 640;
            }
            if (*pointer_y == 900) {
                *pointer_x = 800;
                *pointer_y = 925;
            }

        }
        if (keystates2[SDLK_LEFT]) {
            if (*pointer_y != 925) {
                *pointer_x = 40;
            }
            if (*pointer_y == 925) {
                *pointer_y = 900;
                *pointer_x = 40;
            }
        }
        if (first_menu_pointer_move.type == SDL_QUIT) {
            return false;
        }
    }
    return true;
}

bool last_menu_move_pointer(int *pointer_x, int *pointer_y) {

    Uint8 *keystates3 = SDL_GetKeyState(NULL);
    SDL_Event last_menu_pointer_move;
    if (SDL_PollEvent(&last_menu_pointer_move)) {
        if (keystates3[SDLK_DOWN]) {
            if (*pointer_y != 900) {
                *pointer_y += 125;
            }
        }
        if (keystates3[SDLK_UP]) {
            if (*pointer_y != 775) {
                *pointer_y -= 125;
            }
        }
        if (last_menu_pointer_move.type == SDL_QUIT) {
            return false;
        }
    }
    return true;
}

bool middle_menu_move_pointer(int *pointer_y) {

    Uint8 *keystates4 = SDL_GetKeyState(NULL);
    SDL_Event middle_menu_pointer_move;
    if (SDL_PollEvent(&middle_menu_pointer_move)) {
        if (keystates4[SDLK_DOWN]) {
            if (*pointer_y != 900) {
                *pointer_y += 125;
            }
        }
        if (keystates4[SDLK_UP]) {
            if (*pointer_y != 650) {
                *pointer_y -= 125;
            }
        }
        if (middle_menu_pointer_move.type == SDL_QUIT) {
            return false;
        }
    }
    return true;
}

