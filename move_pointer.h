#include <iostream>
#include <SDL/SDL.h>

//change pointer's x and y

void first_menu_move_pointer(int* pointer_x, int* pointer_y) {
	
	Uint8* keystates2 = SDL_GetKeyState(NULL);
        SDL_Event first_menu_pointer_move;
	if (SDL_PollEvent(&first_menu_pointer_move)) {
		if (keystates2[SDLK_DOWN]) {
			if (*pointer_y != 900 && *pointer_x == 40) {			
				*pointer_y += 125;
			}		
		}
		if (keystates2[SDLK_UP]) {
			if (*pointer_y != 650 && *pointer_x == 40) {
				*pointer_y -= 125;
			}		
		}
		if (keystates2[SDLK_RIGHT]) {
			*pointer_x = 800;
			*pointer_y = 875;
		}
		if (keystates2[SDLK_LEFT]) {
			*pointer_x = 40;
			*pointer_y = 650;
		}
	}
}

void last_menu_move_pointer(int* pointer_x, int* pointer_y) {
	
	Uint8* keystates3 = SDL_GetKeyState(NULL);
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
	}
}

void middle_menu_move_pointer(int* pointer_y) {
	
	Uint8* keystates4 = SDL_GetKeyState(NULL);
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
	}
}

