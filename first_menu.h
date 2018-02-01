#include"applysurface.h"
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
//apply_menu(SDL_Surface *screen, int screenheight, int screenwidth)
int main() {
	
	SDL_Init(SDL_INIT_EVERYTHING);
        TTF_Init();
	int screenheight = 1000;
	int screenwidth = 1000;
	SDL_Surface* screen;
	screen = SDL_SetVideoMode(1000, 1000, 32, 0);	
	SDL_Surface* start;
	SDL_Surface* game_name;	
	SDL_Surface* highscore;
	TTF_Font *menu_font;
	TTF_Font *game_name_font;
        menu_font = TTF_OpenFont("menu.ttf", 32);
	game_name_font = TTF_OpenFont("menu.ttf", 50);
	SDL_Color menu_color = {255, 255, 255};
	while(true) {
	boxRGBA(screen, 0, 0, screenwidth, screenheight, 65, 65, 65, 255);
	boxRGBA(screen, 50, screenheight - 275, 350, screenheight - 175, 255, 75, 0, 200);
	boxRGBA(screen, 50, screenheight - 150, 350, screenheight - 50, 255, 75, 0, 200);

	game_name = TTF_RenderText_Solid(game_name_font, "STAR WARS", menu_color);
	start = TTF_RenderText_Solid(menu_font, "NEW GAME", mrnu_color);
	highscore = TTF_RenderText_Solid(menu_font, "HIGH SCORE", menu_color);

	applysurface(game_name, 400, 300,screen);
	applysurface(start, 150, screenheight - 225, screen);
	applysurface(highscore, 100, screenheight - 225, screen);
	SDL_Flip(screen);
	}
	return 0;
}
