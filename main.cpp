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
#include "sensors.h"
#include "enemies.h"
using namespace std;

int main(int argc ,char * args[])
{

    int arrow_number = 0; // arrow's number that after pressing the space key throw
    int enemy_spaceship_delay;
    int screenwidth = 1000;
    int screenheight = 1000;
    int frame = 0;
    int total_stars = 80;// total number of stars that made till now
    int our_spaceshipx = 450;
    int our_spaceshipy = 870;
    float our_spaceship_right_v = 0;
    float our_spaceship_left_v = 0;

    srand(time(0));
    enemy_spaceship_delay = (rand() % 20) + 100;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen = SDL_SetVideoMode(screenwidth,screenheight,32,0);
    first_space_draw(total_stars , screenheight , screenwidth);
    SDL_Surface* our_spaceship = load_image("our_spaceship.png");
    apply_surface(our_spaceshipx , our_spaceshipy , our_spaceship, screen);
    SDL_WM_SetCaption( "Star Wars", NULL );

    while(true)
    {

        boxRGBA(screen , 0 , 0 , screenwidth , screenheight , 0 , 0 , 50 , 250);

        make_new_star_line(total_stars , screenwidth);

        stars_y_change(total_stars , screenwidth , screenheight);

        draw_stars(screen , total_stars);

        our_spaceship_v_initialize(&our_spaceship_right_v , &our_spaceship_left_v);

        our_spaceship_move ( &our_spaceshipx , &our_spaceship_right_v, &our_spaceship_left_v ,screenwidth , screenheight);

        apply_surface(our_spaceshipx, our_spaceshipy, our_spaceship, screen);

        sensors_position(screen ,our_spaceshipx ,our_spaceshipy);

        arrow_number = make_arrow_ingame(screen, our_spaceshipx, our_spaceshipy, arrow_number);

        move_arrow(screen, arrow_number);

        enemy_spaceships_start_pos(screenwidth ,&enemy_spaceship_delay);

        enemy_spaceships_move(screenheight ,our_spaceshipx);

        show_enemy_spaceships(screen);

        SDL_Flip(screen);

        frame++;

        SDL_Delay(5);

    }

    SDL_Quit();

    return 0;
}
