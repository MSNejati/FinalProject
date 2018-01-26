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
#include "throw_arrows.h"
#include "spaceship_Move.h"

using namespace std;

int main(int argc ,char * args[])
{
    Uint8 *keystates = SDL_GetKeyState( NULL ); 
    int arrow_number = 0; // arrow's number that after pressing the space key throw
    int screenwidth = 1000;
    int screenhieght = 1000;
    int frame = 0;
    int total_stars = 80;// total number of stars that made till now
    int our_spaceshipx = 450;
    int our_spaceshipy = 870;
    float our_spaceship_right_v = 0;
    float our_spaceship_left_v = 0;

    srand(time(0));
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen = SDL_SetVideoMode(screenwidth,screenhieght,32,0);
    first_space_draw(total_stars , screenhieght , screenwidth);
    SDL_Surface* our_spaceship = load_image("our_spaceship.png");
    apply_surface(our_spaceshipx , our_spaceshipy , our_spaceship, screen);
    SDL_WM_SetCaption( "Star Wars", NULL );

    while(true)
    {

        boxRGBA(screen , 0 , 0 , screenwidth , screenhieght , 0 , 0 , 50 , 250);

        make_new_star_line(total_stars , screenwidth);

        stars_y_change(total_stars , screenwidth , screenhieght);

        draw_stars(screen , total_stars);

        our_spaceship_v_initialize(&our_spaceship_right_v , &our_spaceship_left_v);

        our_spaceship_move ( &our_spaceshipx , &our_spaceship_right_v, &our_spaceship_left_v);

        apply_surface(our_spaceshipx, our_spaceshipy, our_spaceship, screen);

	if (keystates[SDLK_SPACE]) {
		make_arrow_ingame(screen, our_spaceshipx, our_spaceshipy, arrow_number);
		arrow_number++;
	}
	
	cout << arrow_number << '\n';
	move_arrow(screen, arrow_number);

        SDL_Flip(screen);

        frame++;

        SDL_Delay(5);

    }

    SDL_Quit();

    return 0;
}
