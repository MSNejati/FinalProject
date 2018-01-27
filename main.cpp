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
    int our_spaceship_heart = 3; // the spaceship's heart in the beginning
    int our_spaceship_bullet = 500; // the spaceship's bullet in the beginning
    int screenwidth = 1010;
    int screenheight = 1010;
    int enemy_spaceship_delay;
    int frame = 0;
    int total_stars = 80;// total number of stars that made till now
    int our_spaceshipx = 450;
    int our_spaceshipy = 880;
    float our_spaceship_right_v = 0;
    float our_spaceship_left_v = 0;

    srand(time(0));
    enemy_spaceship_delay = (rand() % 20) + 100;
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Surface* screen = SDL_SetVideoMode(screenwidth,screenheight,32,0);
    first_space_draw(total_stars , screenheight , screenwidth);
    SDL_Surface* our_spaceship = load_ourspaceship("our_spaceship.png");
    SDL_Surface* heart = load_image("heart.png");
    SDL_Surface* gun_bullet = load_image("gun_bullet.png");
    apply_surface(our_spaceshipx , our_spaceshipy , our_spaceship, screen);
    apply_surface(45, 10, heart, screen);
    apply_surface(930, 10, gun_bullet, screen);
    TTF_Init();
    TTF_Font *toolbar_font;
    toolbar_font = TTF_OpenFont("toolbar.ttf", 32);
    SDL_Color textcolor = {255, 255, 255};
    SDL_Surface *heart_value;
    SDL_Surface *bullet;
    heart_value = make_toolbar_informations(heart_value, toolbar_font, textcolor, our_spaceship_heart);
    bullet = make_toolbar_informations(bullet, toolbar_font, textcolor, our_spaceship_bullet);
    apply_surface(5, 15, heart_value, screen);
    apply_surface(855, 15, bullet, screen);
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

	arrow_number = make_arrow_ingame(screen, our_spaceshipx, our_spaceshipy, arrow_number, our_spaceship_bullet);

	move_arrow(screen, arrow_number);

	enemy_spaceships_start_pos(screenwidth ,&enemy_spaceship_delay);

        enemy_spaceships_move(screenheight ,our_spaceshipx);

        show_enemy_spaceships(screen);

	show_toolbar(screen);

	apply_surface(45, 10, heart, screen);

	apply_surface(930, 10, gun_bullet, screen);
	
	apply_surface(5, 15, heart_value, screen);

        apply_surface(855, 15, bullet, screen);

        SDL_Flip(screen);

        frame++;

        SDL_Delay(5);

    }

    SDL_Quit();

    return 0;
}
