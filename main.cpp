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
    int our_spaceship_bullet = 300; // the spaceship's bullet in the beginning
    int score = 0;
    int highscore = score;
    int screenwidth = 1000;
    int screenheight = 1000;
    int enemy_spaceship_delay;
    int frame = 0;
    int total_stars = 80;// total number of stars that made till now
    int our_spaceshipx = 450;
    int our_spaceshipy = 870;
    int boss_size = 200;
    float stars_speed = 2 ;
    float our_spaceship_right_v = 0;
    float our_spaceship_left_v = 0;
    bool boss_fight = false;

    srand(time(0));
    enemy_spaceship_delay = (rand() % 20) + 100;
    SDL_Init(SDL_INIT_EVERYTHING);

    Uint8 *keystates = SDL_GetKeyState( NULL );
    SDL_Surface* screen = SDL_SetVideoMode(screenwidth,screenheight,32,0);
    first_space_draw(total_stars , screenheight , screenwidth);
    SDL_Surface* our_spaceship = load_ourspaceship("our_spaceship.png");
    SDL_Surface* heart_image = load_image("heart.png");
    SDL_Surface* gun_bullet_image = load_image("gun_bullet.png");
    SDL_Surface* highscore_image = load_image("highscore.png");
    SDL_Surface* score_image = load_image("score.png");
    apply_surface(our_spaceshipx , our_spaceshipy , our_spaceship, screen);
    apply_surface(45, 10, heart_image, screen);
    apply_surface(920, 10, gun_bullet_image, screen);
    apply_surface(665, 10, highscore_image, screen);
    apply_surface(315, 10, score_image, screen);
    TTF_Init();
    TTF_Font *toolbar_font;
    toolbar_font = TTF_OpenFont("toolbar.ttf", 32);
    SDL_Color textcolor = {255, 255, 255};
    SDL_Surface *heart_value;
    SDL_Surface *bullet_value;
    SDL_Surface *score_value;
    SDL_Surface *highscore_value;
    heart_value = make_toolbar_informations(heart_value, toolbar_font, textcolor, our_spaceship_heart);
    bullet_value = make_toolbar_informations(bullet_value, toolbar_font, textcolor, our_spaceship_bullet);
    score_value = make_toolbar_informations(score_value, toolbar_font, textcolor, score);
    highscore_value = make_toolbar_informations(highscore_value, toolbar_font, textcolor, highscore);
    apply_surface(5, 15, heart_value, screen);
    apply_surface(845, 15, bullet_value, screen);
    apply_surface(240, 15, score_value, screen);
    apply_surface(590, 15, highscore_value, screen);
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

        if(boss_fight == false)
        {
            enemy_spaceships_start_pos(screenwidth ,&enemy_spaceship_delay);
        }
        enemy_spaceships_move(screenheight ,our_spaceshipx, &our_spaceship_heart);

        show_enemy_spaceships(screen);

        enemy_shooting();

        move_enemy_arrow (screen);

        if(boss_fight)
        {
            if(boss[0].y <= 150)
            {
                boss_enters();
            }
            else
            {
                boss_x_change(screenwidth ,boss_size);
            }

            show_boss(screen ,boss_size);
        }
        show_toolbar(screen);

        apply_surface(45, 10, heart_image, screen);

        apply_surface(920, 10, gun_bullet_image, screen);

        apply_surface(665, 10, highscore_image, screen);

        apply_surface(315, 10, score_image, screen);

        heart_value = make_toolbar_informations(heart_value, toolbar_font, textcolor, our_spaceship_heart);

        bullet_value = make_toolbar_informations(bullet_value, toolbar_font, textcolor, our_spaceship_bullet);

        score_value = make_toolbar_informations(score_value, toolbar_font, textcolor, score);

        highscore_value = make_toolbar_informations(highscore_value, toolbar_font, textcolor, highscore);

        apply_surface(5, 15, heart_value, screen);

        apply_surface(845, 15, bullet_value, screen);

        apply_surface(240, 15, score_value, screen);

        apply_surface(590, 15, highscore_value, screen);

        sensors_position(screen ,our_spaceshipx ,our_spaceshipy);

        if(collision(&score) == 1)
        {
            our_spaceship_heart--;
        }

        highscore = score;

        if(our_spaceship_heart <= 0)
        {
            break;
        }

        if(score % 10 == 0 && score != 0 && boss_fight == false)
        {
            boss_first_initialize(screenwidth ,boss_size);

            boss_fight = true;
        }

        SDL_Flip(screen);

        frame++;

        SDL_Delay(5);

        }

        SDL_Quit();

        return 0;
}
