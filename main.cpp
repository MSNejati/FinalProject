#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <cstdlib>
#include <ctime>
#include "sstream"
#include <cmath>
#include <fstream>
#include "background.h"
#include "applysurface.h"

using namespace std;

int main(int argc ,char * args[])
{
    int screenwidth = 1000;
    int screenhieght = 1000;
    int frame = 0;
    int total_stars = 80;// total number of stars that made till now
    srand(time(0));
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen = SDL_SetVideoMode(screenwidth,screenhieght,32,0);
    first_space_draw(total_stars , screenhieght , screenwidth);
    SDL_Surface* our_spaceship = load_image("our_spaceship.png"); 
    apply_surface(450, 870, our_spaceship, screen);
    SDL_WM_SetCaption( "Star Wars", NULL );

    while(true)
    {

        boxRGBA(screen , 0 , 0 , screenwidth , screenhieght , 0 , 0 , 50 , 250);
        make_new_star_line(total_stars , screenwidth);
        stars_y_change(total_stars , screenwidth , screenhieght);
        draw_stars(screen , total_stars);
	apply_surface(450, 870, our_spaceship, screen);
        SDL_Flip(screen);
        frame++;
        SDL_Delay(5);

    }

    SDL_Quit();

    return 0;
}
