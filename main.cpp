#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include "sstream"
#include <cmath>
#include <fstream>
#include "spaceship_Move.h"
#include "move_pointer.h"
#include "speedandlevel.h"

using namespace std;

int main(int argc, char *args[]) {

    int arrow_number = 0; // arrow's number that after pressing the space key throw
    int our_spaceship_heart = 3; // the spaceship's heart in the beginning
    int our_spaceship_bullet = 300; // the spaceship's bullet in the beginning
    int score = 0;
    int level = 1;
    int highscore = score;
    int screenwidth = 1000;
    int screenheight = 1000;
    int enemy_spaceship_delay;
    int frame = 0;
    int total_stars = 80;// total number of stars that made till now
    int our_spaceshipx = 450;
    int our_spaceshipy = 870;
    int boss_size = 200;
    int max_enemies_count = 1;
    int max_enemies_enter_delay = 200;
    float stars_speed = 2;
    float our_spaceship_right_v = 0;
    float our_spaceship_left_v = 0;
    bool boss_fight = false;
    bool first_menu = true;
    bool last_menu = false;
    string enemy_type = "enemyspaceship.png";

    srand(time(0));
    enemy_spaceship_delay = (rand() % max_enemies_enter_delay / 10) + 100;
    SDL_Init(SDL_INIT_EVERYTHING);

    Uint8 *keystates = SDL_GetKeyState(NULL);
    SDL_Surface *screen = SDL_SetVideoMode(screenwidth, screenheight, 32, 0);
    first_space_draw(total_stars, screenheight, screenwidth);
    SDL_Surface *our_spaceship = load_ourspaceship("our_spaceship.png");
    SDL_Surface *heart_image = load_image("heart.png");
    SDL_Surface *gun_bullet_image = load_image("gun_bullet.png");
    SDL_Surface *highscore_image = load_image("highscore.png");
    SDL_Surface *score_image = load_image("score.png");
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
    SDL_WM_SetCaption("Star Wars", NULL);

    for (int i = 0; i < 5; i++) {
        our[i].ingame = true; //make our spaceship sensor in game
    }

    SDL_Surface *start;
    SDL_Surface *first_menu_exit;
    SDL_Surface *game_name;
    SDL_Surface *first_menu_highscore;
    SDL_Surface *first_menu_highscore_value;
    SDL_Surface *meteorite;
    SDL_Surface *volume_on;
    SDL_Surface *volume_off;
    TTF_Font *menu_font;
    menu_font = TTF_OpenFont("menu.ttf", 36);
    SDL_Color menu_color = {255, 255, 255};
    game_name = load_image("game_name.png");
    meteorite = load_image("meteorite.png");
    volume_on = load_image("volume_on.png");
    volume_off = load_image("volume_off.png");
    start = TTF_RenderText_Solid(menu_font, "NEW GAME", menu_color);
    first_menu_highscore = TTF_RenderText_Solid(menu_font, "HIGH SCORE", menu_color);
    first_menu_exit = TTF_RenderText_Solid(menu_font, "EXIT", menu_color);
    int meteorite_x = 1200;
    int meteorite_y = -800;
    int m;
    int n = (rand() % 3000) + 4000;
    int meteorite_yv = 15;
    int meteorite_xv = -15;
    bool volume = true;
    int first_menu_pointer_x = 40;
    int first_menu_pointer_y = 650;
    bool bool_first_menu_highscore = false;
    int volume_delay = 0;

    int gameover_y = -400;
    SDL_Surface* last_menu_score;
    SDL_Surface* restart;
    SDL_Surface* gameover;
    SDL_Surface* last_menu_exit;
    last_menu_exit = TTF_RenderText_Solid(menu_font, "EXIT", menu_color);
    gameover = load_image("gameover.png");
    restart = TTF_RenderText_Solid(menu_font, "RESTART", menu_color);
    last_menu_score = TTF_RenderText_Solid(menu_font, "SCORE :", menu_color);
    int last_menu_pointer_x = 340;
    int last_menu_pointer_y = 775;

    while (true) {

        if (first_menu == true)
         {

            boxRGBA(screen, 0, 0, screenwidth, screenheight, 45, 45, 45, 255);
            apply_surface(meteorite_x, meteorite_y, meteorite, screen);
            meteorite_x = meteorite_x + meteorite_xv;
            meteorite_y = meteorite_y + meteorite_yv;
	    boxRGBA(screen, 50, screenheight - 400, 350, screenheight - 300, 255, 75, 0, 200);
            boxRGBA(screen, 50, screenheight - 275, 350, screenheight - 175, 255, 75, 0, 200);
            boxRGBA(screen, 50, screenheight - 150, 350, screenheight - 50, 255, 75, 0, 200);
            apply_surface(250, 100, game_name, screen);
            apply_surface(100, screenheight - 373, start, screen);
	    apply_surface(160, screenheight - 123, first_menu_exit, screen);
	    first_menu_move_pointer(&first_menu_pointer_x, &first_menu_pointer_y);
	    filledCircleRGBA(screen, first_menu_pointer_x, first_menu_pointer_y, 5, 0, 254, 0, 200);

            if (keystates[SDLK_RCTRL]) {
		if (first_menu_pointer_y == 650) {
		    first_menu = false;
		}
		if (first_menu_pointer_y == 775) {
		    bool_first_menu_highscore = true;
		}
		if (first_menu_pointer_y == 900) {
		    TTF_CloseFont(menu_font);
                    TTF_CloseFont(toolbar_font);
                    SDL_FreeSurface(screen);
                    SDL_FreeSurface(our_spaceship);
                    SDL_FreeSurface(heart_image);
                    SDL_FreeSurface(gun_bullet_image);
                    SDL_FreeSurface(highscore_image);
                    SDL_FreeSurface(score_image);
		    SDL_FreeSurface(heart_value);
		    SDL_FreeSurface(bullet_value);
		    SDL_FreeSurface(highscore_value);
		    SDL_FreeSurface(start);
		    SDL_FreeSurface(first_menu_exit);
		    SDL_FreeSurface(game_name);
		    SDL_FreeSurface(first_menu_highscore);
		    SDL_FreeSurface(meteorite);
		    SDL_FreeSurface(volume_on);
		    SDL_FreeSurface(volume_off);
		    SDL_FreeSurface(last_menu_score);
		    SDL_FreeSurface(restart);
		    SDL_FreeSurface(gameover);
		    SDL_FreeSurface(last_menu_exit);
		    TTF_Quit();
                    SDL_Quit();
		    return 0;
		}
		if (first_menu_pointer_y == 875) {
		    if (volume_delay % 10 == 0) {
		    	if (volume == true) {
		        	volume = false;
				volume_delay = 1;
				//set volume to zero

		    	}
		    	else {
                    volume = true;
                    volume_delay = 1;
                    //set volume to 100%
		    	}
		    }
		    else {
                volume_delay++;
		    }
		}
	    }

	    if(!keystates[SDLK_RCTRL]) {
            volume_delay = 0;
	    }

            if (meteorite_x <= -1 * n) {
                meteorite_x = 1100;
                m = rand() % 9;
                n = (rand() % 3000) + 4000;
                meteorite_y = -800 + (m * 200);
            }

	    if (volume == true) {
                apply_surface(screenwidth - 200, screenheight - 200, volume_on, screen);
            }

            if (volume == false) {
                apply_surface(screenwidth - 200, screenheight - 200, volume_off, screen);
            }

	    if (bool_first_menu_highscore == true) {
		//show highscore
	    }

	    if (bool_first_menu_highscore == false) {
		apply_surface(95, screenheight - 248, first_menu_highscore, screen);
	    }

        }

        if (first_menu == false && last_menu == false) {

            boxRGBA(screen, 0, 0, screenwidth, screenheight, 0, 0, 50, 250);
            make_new_star_line(total_stars, screenwidth);
            stars_y_change(total_stars, screenwidth, screenheight);
            draw_stars(screen, total_stars);
            our_spaceship_v_initialize(&our_spaceship_right_v, &our_spaceship_left_v);
            our_spaceship_move(&our_spaceshipx, &our_spaceship_right_v, &our_spaceship_left_v, screenwidth, screenheight);
            apply_surface(our_spaceshipx, our_spaceshipy, our_spaceship, screen);

            if (keystates[SDLK_SPACE]) {
                if (arrow_delay % 10 == 0 && our_spaceship_bullet > 0) {
                    arrow_number = make_arrow_ingame(screen, our_spaceshipx, our_spaceshipy, arrow_number);
                    arrow_delay = 1;
                    our_spaceship_bullet--;
                } else {
                    arrow_delay++;
                }
            }

            if (!keystates[SDLK_SPACE]) {
                arrow_delay = 0;
            }

            move_arrow(screen);

            if (boss_fight == false) {
                enemy_spaceships_start_pos(screenwidth, &enemy_spaceship_delay , max_enemies_enter_delay ,max_enemies_count);
            }

            enemy_spaceships_move(screenheight, our_spaceshipx, &our_spaceship_heart);
            show_enemy_spaceships(screen ,enemy_type);
            enemy_shooting();
            move_enemy_arrow(screen);

            if (boss_fight) {
                if (boss[0].y <= 150) {
                    boss_enters();
                } else {
                    boss_x_change(screenwidth, boss_size);
                    enemy_boss_shooting();
                    move_enemy_boss_arrow(screen, screenheight);
                    if (collision( boss_fight) == 1) {
                        our_spaceship_heart--;
                    }
                    show_boss_health_bar(screen);
                }
                show_boss(screen, boss_size);
                boss_sensors_position(screen);
                boss_collision_check();
                if (boss[0].hitpoint <= 0)
                {
                    level++;
                    level_difficulity(level ,&max_enemies_count ,&max_enemies_enter_delay ,&enemy_type);
                    boss_fight = false ;
                    destroy_the_boss();
                }
            }

           if(keystates[SDLK_UP])
            {
                speed_change(1);
            }
            if(keystates[SDLK_DOWN])
            {
                speed_change(-1);
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
            sensors_position(screen, our_spaceshipx, our_spaceshipy);

            if (collision( boss_fight) == 1) {
                our_spaceship_heart--;
            }

            highscore = score;

            if (our_spaceship_heart <= 0) {
                last_menu = true;
            }

            if(frame >= (100 - (star[0].yv*5)) && boss_fight == false)
            {
                frame = 0;
                score++;
            }

            if (score % 10 == 0 && score != 0 && boss_fight == false) {
                boss_first_initialize(screenwidth, boss_size);
                boss_fight = true;
            }

            frame++;

        }

        if (last_menu == true) {

	    score_value = score_value = make_toolbar_informations(score_value, menu_font, textcolor, score);
            boxRGBA(screen, 0, 0, screenwidth, screenheight, 45, 45, 45, 255);
            if (gameover_y != 50) {
		gameover_y += 1;
	        apply_surface(250, gameover_y, gameover, screen);
            }
	    if (gameover_y == 50) {
		apply_surface(250, gameover_y, gameover, screen);
	    }
	    boxRGBA(screen, 190, screenheight - 400, 490, screenheight - 300, 0, 175, 255, 200);
            boxRGBA(screen, 510, screenheight - 400, 810, screenheight - 300, 0, 175, 255, 200);
	    boxRGBA(screen, 350, screenheight - 275, 650, screenheight - 175, 255, 75, 0, 200);
	    boxRGBA(screen, 350, screenheight - 150, 650, screenheight - 50, 255, 75, 0, 200);
            apply_surface(278, screenheight - 375, last_menu_score, screen);
            apply_surface(425, screenheight - 248, restart, screen);
	    apply_surface(460, screenheight - 123, last_menu_exit, screen);
	    if (score < 10) {
	    	apply_surface(650, screenheight - 372, score_value, screen);
	    }
	    if (score < 100 && score >= 10) {
		apply_surface(640, screenheight - 372, score_value, screen);
	    }
	    if (score < 1000 && score >= 100) {
		apply_surface(630, screenheight - 372, score_value, screen);
	    }
	    if (score < 10000 && score >= 1000) {
		apply_surface(620, screenheight - 372, score_value, screen);
	    }
	    if (score < 100000 && score >= 10000) {
		apply_surface(610, screenheight - 372, score_value, screen);
	    }
 	    if (score < 1000000 && score >= 100000) {
		apply_surface(600, screenheight - 372, score_value, screen);
	    }
	    if (score < 10000000 && score >= 1000000) {
		apply_surface(590, screenheight - 372, score_value, screen);
	    }
	    last_menu_move_pointer(&last_menu_pointer_x, &last_menu_pointer_y);
	    filledCircleRGBA(screen, last_menu_pointer_x, last_menu_pointer_y, 5, 0, 254, 0, 200);

	    if (keystates[SDLK_RCTRL]) {
		if (last_menu_pointer_y == 900) {
		    TTF_CloseFont(menu_font);
                    TTF_CloseFont(toolbar_font);
                    SDL_FreeSurface(screen);
                    SDL_FreeSurface(our_spaceship);
                    SDL_FreeSurface(heart_image);
                    SDL_FreeSurface(gun_bullet_image);
                    SDL_FreeSurface(highscore_image);
                    SDL_FreeSurface(score_image);
		    SDL_FreeSurface(heart_value);
		    SDL_FreeSurface(bullet_value);
		    SDL_FreeSurface(highscore_value);
		    SDL_FreeSurface(start);
		    SDL_FreeSurface(first_menu_exit);
		    SDL_FreeSurface(game_name);
		    SDL_FreeSurface(first_menu_highscore);
		    SDL_FreeSurface(meteorite);
		    SDL_FreeSurface(volume_on);
		    SDL_FreeSurface(volume_off);
		    SDL_FreeSurface(last_menu_score);
		    SDL_FreeSurface(restart);
		    SDL_FreeSurface(gameover);
		    SDL_FreeSurface(last_menu_exit);
		    TTF_Quit();
                    SDL_Quit();
		    return 0;
		}
		if (last_menu_pointer_y == 775) {
			//restart (set all data to their first value and save score if it is higher than the last highscore)
		}
	    }
        }

        SDL_Flip(screen);
        SDL_Delay(5);
    }

    SDL_Quit();

    return 0;
}
