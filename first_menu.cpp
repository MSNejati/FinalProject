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

//apply_first_menu(SDL_Surface *screen, int screenheight, int screenwidth) {

int main() {
	
	srand(time(0));
	SDL_Init(SDL_INIT_EVERYTHING);
        TTF_Init();
	int screenheight = 1000;
	int screenwidth = 1000;
	SDL_Surface* screen;
	screen = SDL_SetVideoMode(1000, 1000, 32, 0);	
	SDL_Surface* start;
	SDL_Surface* game_name;	
	SDL_Surface* highscore;
	SDL_Surface* meteorite;
	SDL_Surface* volume_on;
	SDL_Surface* volume_off;
	TTF_Font *menu_font;
        menu_font = TTF_OpenFont("menu.ttf", 32);
	SDL_Color menu_color = {255, 255, 255};
	game_name = load_image("game_name.png");
	meteorite = load_image("meteorite.png");
	volume_on = load_image("volume_on.png");
	volume_off = load_image("volume_off.png");	
	start = TTF_RenderText_Solid(menu_font, "NEW GAME", menu_color);
	highscore = TTF_RenderText_Solid(menu_font, "HIGH SCORE", menu_color);
	int meteorite_x = 1200;
	int meteorite_y = -800;
	int m;
	int n = (rand() % 3000) + 4000;  
	int meteorite_yv = 15;
	int meteorite_xv = -15;
	bool volume = true;

	while(true) {
	
		boxRGBA(screen, 0, 0, screenwidth, screenheight, 45, 45, 45, 255);
		apply_surface(meteorite_x, meteorite_y, meteorite, screen);	
		meteorite_x = meteorite_x + meteorite_xv;
		meteorite_y = meteorite_y + meteorite_yv;	
		boxRGBA(screen, 50, screenheight - 275, 350, screenheight - 175, 255, 75, 0, 200);
		boxRGBA(screen, 50, screenheight - 150, 350, screenheight - 50, 255, 75, 0, 200);
		apply_surface(250, 100, game_name, screen);
		apply_surface(110, screenheight - 245, start, screen);
		apply_surface(100, screenheight - 120, highscore, screen);
		if (volume == true) {		
			apply_surface(screenwidth - 200, screenheight - 200, volume_on, screen);
		
		}
		else {
			apply_surface(screenwidth - 200, screenheight - 200, volume_off, screen);
		}
		SDL_Flip(screen);
		SDL_Delay(5);
		if (meteorite_x <= -1 * n) {
			meteorite_x = 1100;
			m = rand() % 9;
			n = (rand() % 3000) + 4000;
			meteorite_y = - 800 + (m * 200);
		}
	}
	return 0;
}
