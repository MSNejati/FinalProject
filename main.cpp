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
//#include "applysurface.h"
//#include "throw_arrows.h"
#include "spaceship_Move.h"
#include "sensorsandcollision.h"

using namespace std;

int main(int argc ,char * args[])
{

    int arrow_number = 0; // arrow's number that after pressing the space key throw
    int our_spaceship_heart = 3; // the spaceship's heart in the beginning
    int our_spaceship_bullet = 500; // the spaceship's bullet in the beginning
    int screenwidth = 1000;
    int screenheight = 1000;
    int enemy_spaceship_delay;
    int frame = 0;
    int total_stars = 80;// total number of stars that made till now
    int our_spaceshipx = 450;
    int our_spaceshipy = 870;
    float our_spaceship_right_v = 0;
    float our_spaceship_left_v = 0;

    srand(time(0));
    enemy_spaceship_delay = (rand() % 20) + 100;
    SDL_Init(SDL_INIT_EVERYTHING);

    Uint8 *keystates = SDL_GetKeyState( NULL );
    SDL_Surface* screen = SDL_SetVideoMode(screenwidth,screenheight,32,0);
    first_space_draw(total_stars , screenheight , screenwidth);
    SDL_Surface* our_spaceship = load_ourspaceship("our_spaceship.png");
    SDL_Surface* heart = load_image("heart.png");
    SDL_Surface* gun_bullet = load_image("gun_bullet.png");
    SDL_Surface* highscore = load_image("highscore.png");
    SDL_Surface* score = load_image("score.png");
    apply_surface(our_spaceshipx , our_spaceshipy , our_spaceship, screen);
    apply_surface(45, 10, heart, screen);
    apply_surface(920, 10, gun_bullet, screen);
    apply_surface(665, 10, highscore, screen);
    apply_surface(315, 10, score, screen);
    TTF_Init();
    TTF_Font *toolbar_font;
    toolbar_font = TTF_OpenFont("toolbar.ttf", 32);
    SDL_Color textcolor = {255, 255, 255};
    SDL_Surface *heart_value;
    SDL_Surface *bullet;
    heart_value = make_toolbar_informations(heart_value, toolbar_font, textcolor, our_spaceship_heart);
    bullet = make_toolbar_informations(bullet, toolbar_font, textcolor, our_spaceship_bullet);
    apply_surface(5, 15, heart_value, screen);
    apply_surface(845, 15, bullet, screen);
    SDL_WM_SetCaption( "Star Wars", NULL );

    for(int i = 0; i < 5 ; i++)
    {
        our[i].ingame = true ; //make our spaceship sensor in game
    }

    while(true)
    {

        boxRGBA(screen , 0 , 0 , screenwidth , screenheight , 0 , 0 , 50 , 250);

        make_new_star_line(total_stars , screenwidth);

        stars_y_change(total_stars , screenwidth , screenheight);

        draw_stars(screen , total_stars);

        our_spaceship_v_initialize(&our_spaceship_right_v , &our_spaceship_left_v);

        our_spaceship_move ( &our_spaceshipx , &our_spaceship_right_v, &our_spaceship_left_v ,screenwidth , screenheight);

        apply_surface(our_spaceshipx, our_spaceshipy, our_spaceship, screen);



	if (keystates[SDLK_SPACE])
	{
		if(arrow_delay % 10 == 0 && our_spaceship_bullet > 0)
       		{
			arrow_number = make_arrow_ingame(screen, our_spaceshipx, our_spaceshipy, arrow_number);
			arrow_delay = 1;
			our_spaceship_bullet--;
		}
		else
		{
			arrow_delay++;
		}

	}
	if (!keystates[SDLK_SPACE]) {

		arrow_delay = 0;
	}

	move_arrow(screen);

	enemy_spaceships_start_pos(screenwidth ,&enemy_spaceship_delay);

        enemy_spaceships_move(screenheight ,our_spaceshipx);

        show_enemy_spaceships(screen);

        enemy_shooting();

        move_enemy_arrow (screen);

	show_toolbar(screen);

	apply_surface(45, 10, heart, screen);

	apply_surface(920, 10, gun_bullet, screen);

	apply_surface(665, 10, highscore, screen);

        apply_surface(315, 10, score, screen);

	heart_value = make_toolbar_informations(heart_value, toolbar_font, textcolor, our_spaceship_heart);

        bullet = make_toolbar_informations(bullet, toolbar_font, textcolor, our_spaceship_bullet);

	apply_surface(5, 15, heart_value, screen);

        apply_surface(845, 15, bullet, screen);

        sensors_position(screen ,our_spaceshipx ,our_spaceshipy);

        collision();

        SDL_Flip(screen);

        frame++;

        SDL_Delay(5);

    }

    SDL_Quit();

    return 0;
}
