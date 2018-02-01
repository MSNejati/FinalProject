#include "applysurface.h"
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <cstdlib>
#include <string>
#include <ctime>
#include "sstream"
#include <cmath>
#include <fstream>
#include <iostream>
//apply_last_menu(SDL_Surface* screen, int screenheight, int screenwidth, int* score)
int main() {
	
	srand(time(0));
	SDL_Init(SDL_INIT_EVERYTHING);
        TTF_Init();
	int screenheight = 1000;
	int screenwidth = 1000;
	SDL_Surface* screen;
	SDL_Surface* score;
	SDL_Surface* restart;
	screen = SDL_SetVideoMode(1000, 1000, 32, 0);
	SDL_Surface* gameover;
	gameover = load_image("gameover.png");
	restart = load_image("restart.png");
	TTF_Font *menu_font;
        menu_font = TTF_OpenFont("menu.ttf", 36);
	SDL_Color menu_color = {255, 255, 255};
	score = TTF_RenderText_Solid(menu_font, "SCORE :", menu_color);

	while(true) {
	
		boxRGBA(screen, 0, 0, screenwidth, screenheight, 45, 45, 45, 255);
		apply_surface(250, 100, gameover, screen);
		boxRGBA(screen, 190, screenheight - 275, 490, screenheight - 175, 0, 175, 255, 200);
		boxRGBA(screen, 510, screenheight - 275, 810, screenheight - 175, 0, 175, 255, 200);
		apply_surface(278, screenheight - 250, score, screen);
		apply_surface(425, screenheight - 165, restart, screen);
		SDL_Flip(screen);
	
	}
	return 0;
}

