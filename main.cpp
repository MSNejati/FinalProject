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
#include "power_ups.h"

using namespace std;

int main(int argc, char *args[]) {

    srand(time(0));
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_Chunk *our_shot = NULL;
    our_shot = Mix_LoadWAV("our_shoting_sound.wav");
    Mix_Chunk *enemy_shot = NULL;
    enemy_shot = Mix_LoadWAV("enemy_shoting_sound.wav");
    Mix_Chunk *boss_shot = NULL;
    boss_shot = Mix_LoadWAV("boss_shoting_sound.wav");
    Mix_Music *first_menu_music = NULL;
    first_menu_music = Mix_LoadMUS("first_menu_music.wav");
    Mix_Chunk *gameover_sound = NULL;
    bool last_music_play = true;
    gameover_sound = Mix_LoadWAV("gameover_sound.wav");
    Mix_Chunk *explosion_sound = NULL;
    explosion_sound = Mix_LoadWAV("explosion.wav");


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
    int our_explo_frame = 2;
    int boss_explo_frame = 0;
    int boss_size = 200;
    int max_enemies_count = 1;
    int max_enemies_enter_delay = 300;
    int show_level_frame = 1;
    int power_up_drop_timer = (rand() % 300) + 500;
    int power_up_type = rand() % 3;
    int laser_count = 0;
    int laser_delay_counter = 10;
    int red_meteorite_counter = (rand() % 300) + 500;
    float stars_speed = 2;
    float our_spaceship_right_v = 0;
    float our_spaceship_left_v = 0;
    bool boss_fight = false;
    bool first_menu = true;
    bool last_menu = false;
    bool middle_menu = false;
    bool game_over = false;

    string enemy_type = "enemyspaceship.png";


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
    SDL_Surface *red_meteorite_img = load_image("red_meteorite.png");
    TTF_Init();
    TTF_Font *toolbar_font;
    TTF_Font *SAN_font = TTF_OpenFont("laser.ttf", 20);
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
    red_meteorite_speed_init();

    for (int i = 0; i < 5; i++) {
        our[i].ingame = true; //make our spaceship sensor in game
    }

    SDL_Surface *start;
    SDL_Surface *help;
    SDL_Surface *first_menu_exit;
    SDL_Surface *game_name;
    SDL_Surface *first_menu_highscore;
    SDL_Surface *first_menu_highscore_value;
    SDL_Surface *meteorite;
    SDL_Surface *volume_on;
    SDL_Surface *volume_off;
    SDL_Surface *special_ammu_key;
    SDL_Surface *pause_key;
    SDL_Surface *moving_key;
    SDL_Surface *shooting_key;
    SDL_Surface *credits;
    SDL_Surface *designer1;
    SDL_Surface *designer2;
    TTF_Font *menu_font;
    TTF_Font *help_font;
    TTF_Font *credits_font;
    menu_font = TTF_OpenFont("menu.ttf", 32);
    help_font = TTF_OpenFont("menu.ttf", 18);
    credits_font = TTF_OpenFont("menu.ttf", 20);
    SDL_Color menu_color = {255, 255, 255};
    game_name = load_image("game_name.png");
    meteorite = load_image("meteorite.png");
    volume_on = load_image("volume_on.png");
    volume_off = load_image("volume_off.png");
    start = TTF_RenderText_Solid(menu_font, "NEW GAME", menu_color);
    first_menu_highscore = TTF_RenderText_Solid(menu_font, "HIGH SCORE", menu_color);
    first_menu_exit = TTF_RenderText_Solid(menu_font, "EXIT", menu_color);
    help = TTF_RenderText_Solid(menu_font, "HELP", menu_color);
    special_ammu_key = TTF_RenderText_Solid(help_font, "N : special ammu", menu_color);
    pause_key = TTF_RenderText_Solid(help_font, " ESC : paused menu", menu_color);
    moving_key = TTF_RenderText_Solid(help_font, "ARROW KEYS : moving", menu_color);
    shooting_key = TTF_RenderText_Solid(help_font, "SPACE : shooting", menu_color);
    credits = TTF_RenderText_Solid(menu_font, "DESIGNERS", menu_color);
    designer1 = TTF_RenderText_Solid(credits_font, "AhmadReza SanaatJo", menu_color);
    designer2 = TTF_RenderText_Solid(credits_font, "MohammadSajjad Nejati", menu_color);
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
    int help_delay = 0;
    int highscore_delay = 0;
    int designers_delay = 0;
    Mix_PlayMusic(first_menu_music, -1);
    bool help_menu = false;
    bool designers = false;

    SDL_Surface *paused_message;
    TTF_Font *paused_font;
    paused_font = TTF_OpenFont("menu.ttf", 80);
    paused_message = TTF_RenderText_Solid(paused_font, "PAUSED", menu_color);
    SDL_Surface *middle_menu_exit;
    middle_menu_exit = TTF_RenderText_Solid(menu_font, "EXIT", menu_color);
    SDL_Surface *middle_menu_restart;
    middle_menu_restart = TTF_RenderText_Solid(menu_font, "RESTART", menu_color);
    SDL_Surface *resume;
    resume = TTF_RenderText_Solid(menu_font, "RESUME", menu_color);
    int middle_menu_pointer_x = 340;
    int middle_menu_pointer_y = 650;

    int gameover_y = -400;
    SDL_Surface *last_menu_score;
    SDL_Surface *restart;
    SDL_Surface *gameover;
    SDL_Surface *last_menu_exit;
    SDL_Surface *new_highscore_image;
    last_menu_exit = TTF_RenderText_Solid(menu_font, "EXIT", menu_color);
    gameover = load_image("gameover.png");
    new_highscore_image = load_image("new_highscore.png");
    restart = TTF_RenderText_Solid(menu_font, "RESTART", menu_color);
    last_menu_score = TTF_RenderText_Solid(menu_font, "SCORE :", menu_color);
    int last_menu_pointer_x = 340;
    int last_menu_pointer_y = 775;
    bool last_menu_highscore_image = false;

    while (true) {

        if (first_menu == true) {
            ifstream high_score_in("high_score");
            high_score_in >> highscore;
            high_score_in.close();
            //gereftan high score

            boxRGBA(screen, 0, 0, screenwidth, screenheight, 45, 45, 45, 255);
            apply_surface(meteorite_x, meteorite_y, meteorite, screen);
            meteorite_x = meteorite_x + meteorite_xv;
            meteorite_y = meteorite_y + meteorite_yv;
            boxRGBA(screen, 50, screenheight - 400, 350, screenheight - 300, 255, 75, 0, 200);
            boxRGBA(screen, 50, screenheight - 275, 350, screenheight - 175, 255, 75, 0, 200);
            boxRGBA(screen, 50, screenheight - 150, 350, screenheight - 50, 255, 75, 0, 200);
            apply_surface(250, 100, game_name, screen);
            apply_surface(90, screenheight - 367, start, screen);
            apply_surface(155, screenheight - 117, first_menu_exit, screen);
            if (first_menu_move_pointer(&first_menu_pointer_x, &first_menu_pointer_y) == false) {
                return 0;
            }

            filledCircleRGBA(screen, first_menu_pointer_x, first_menu_pointer_y, 5, 0, 254, 0, 200);

            if (keystates[SDLK_RCTRL]) {
                if (first_menu_pointer_y == 650 && first_menu_pointer_x == 40) {
                    first_menu = false;
                }
                if (first_menu_pointer_y == 650 && first_menu_pointer_x == 640) {
                    if (help_delay % 10 == 0) {
                        if (help_menu == false) {
                            help_menu = true;
                            help_delay = 1;
                        } else {
                            help_menu = false;
                            help_delay = 1;
                        }
                    }
                    else {
                        help_delay++;
                    }
                }
                if (first_menu_pointer_y == 775 && first_menu_pointer_x == 40) {
                    if (highscore_delay % 10 == 0) {
                        if (bool_first_menu_highscore == false) {
                            bool_first_menu_highscore = true;
                            highscore_delay = 1;
                        } else {
                            bool_first_menu_highscore = false;
                            highscore_delay = 1;
                        }
                    }
                    else {
                        highscore_delay++;
                    }
                }
                if (first_menu_pointer_y == 775 && first_menu_pointer_x == 640) {
                    if (designers_delay % 10 == 0) {
                        if (designers == false) {
                            designers = true;
                            designers_delay = 1;
                        } else {
                            designers = false;
                            designers_delay = 1;
                        }
                    }
                    else {
                        designers_delay++;
                    }
                }
                if (first_menu_pointer_y == 900) {
                    return 0;
                }
                if (first_menu_pointer_y == 925) {
                    if (volume_delay % 10 == 0) {
                        if (volume == true) {
                            volume = false;
                            volume_delay = 1;
                        } else {
                            volume = true;
                            volume_delay = 1;
                        }
                    } else {
                        volume_delay++;
                    }
                }
            }

            if (!keystates[SDLK_RCTRL]) {
                volume_delay = 0;
            }

            if (meteorite_x <= -1 * n) {
                meteorite_x = 1100;
                m = rand() % 9;
                n = (rand() % 3000) + 4000;
                meteorite_y = -800 + (m * 200);
            }

            if (volume == true) {
                apply_surface(screenwidth - 200, screenheight - 150, volume_on, screen);
                Mix_ResumeMusic();
            }

            if (volume == false) {
                apply_surface(screenwidth - 200, screenheight - 150, volume_off, screen);
                Mix_PauseMusic();
            }

            if (bool_first_menu_highscore == true) {
                first_menu_highscore_value = make_toolbar_informations(first_menu_highscore_value, menu_font,
                                                                       menu_color, highscore);
                if (highscore < 10) {
                    apply_surface(177, screenheight - 245, first_menu_highscore_value, screen);
                }
                if (highscore < 100 && highscore >= 10) {
                    apply_surface(167, screenheight - 242, first_menu_highscore_value, screen);
                }
                if (highscore < 1000 && highscore >= 100) {
                    apply_surface(157, screenheight - 242, first_menu_highscore_value, screen);
                }
                if (highscore < 10000 && highscore >= 1000) {
                    apply_surface(147, screenheight - 242, first_menu_highscore_value, screen);
                }
                if (highscore < 100000 && highscore >= 10000) {
                    apply_surface(137, screenheight - 242, first_menu_highscore_value, screen);
                }
                if (highscore < 1000000 && highscore >= 100000) {
                    apply_surface(127, screenheight - 242, first_menu_highscore_value, screen);
                }
                if (highscore < 10000000 && highscore >= 1000000) {
                    apply_surface(117, screenheight - 242, first_menu_highscore_value, screen);
                }
            }

            if (bool_first_menu_highscore == false) {
                apply_surface(85, screenheight - 242, first_menu_highscore, screen);
            }

            if (help_menu == true) {
                boxRGBA(screen, 650, screenheight - 470, 950, screenheight - 300, 255, 75, 0, 200);
                apply_surface(682, screenheight - 443, moving_key, screen);
                apply_surface(682, screenheight - 413, shooting_key, screen);
                apply_surface(682, screenheight - 383, special_ammu_key, screen);
                apply_surface(675, screenheight - 353, pause_key, screen);
            }
            if (help_menu == false) {
                boxRGBA(screen, 650, screenheight - 400, 950, screenheight - 300, 255, 75, 0, 200);
                apply_surface(750, screenheight - 367, help, screen);
            }
            if (designers == false) {
                boxRGBA(screen, 650, screenheight - 275, 950, screenheight - 175, 255, 75, 0, 200);
                apply_surface(690, screenheight - 242, credits, screen);
            }
            if (designers == true) {
                boxRGBA(screen, 650, screenheight - 275, 950, screenheight - 175, 0, 175, 255, 200);
                apply_surface(674, screenheight - 250, designer1, screen);
                apply_surface(663, screenheight - 220, designer2, screen);
            }
        }

        if (first_menu == false && last_menu == false && middle_menu == false) {

            ofstream high_score_out("high_score");
            high_score_out << highscore;
            high_score_out.close();
            //dadan high score
            if (score > highscore) {
                highscore = score;
                last_menu_highscore_image = true;
            }

            Mix_HaltMusic();
            boxRGBA(screen, 0, 0, screenwidth, screenheight, 0, 0, 50, 250);
            make_new_star_line(total_stars, screenwidth);
            stars_y_change(total_stars, screenwidth, screenheight);
            draw_stars(screen, total_stars);
            if (our_spaceship_v_initialize(&our_spaceship_right_v, &our_spaceship_left_v) == false) {
                return  0;
            }

            power_up_move_and_show(screen);

            //=====================red meteorite=====================================

            red_meteorite_counter--;
            if (red_meteorite_counter == 0 && red_meteorite[0].ingame == false) {
                red_meteorite_counter = (rand() % 300) + 500;
                red_meteorite_place_init();
            }
            if (red_meteorite[0].ingame == true) {
                red_meteorite_move(red_meteorite_img, screen);
            }

            if (red_meteorite[0].x > screenwidth) {
                red_meteorite[0].ingame = false;
            }

            if (red_meteorite_collision() == 1) {
                our_spaceship_heart--;
            }

            //=======================================================================

            our_spaceship_move(&our_spaceshipx, &our_spaceship_right_v, &our_spaceship_left_v, screenwidth,
                               screenheight);
            if (game_over == false) {
                apply_surface(our_spaceshipx, our_spaceshipy, our_spaceship, screen);
            }
            //===========================power up=======================================

            power_up_drop_timer--;
            if (power_up_drop_timer == 0) {
                power_up_drop(power_up_type);
                power_up_drop_timer = (rand() % 300) + 500;
                power_up_type = rand() % 3;

            }
            if (catch_power_ups(&laser_count) == 0) {
                our_spaceship_heart++;
                extra_heart[0].ingame = false;
            } else if (catch_power_ups(&laser_count) == 1) {
                our_spaceship_bullet += 50;
                extra_bullet[0].ingame = false;
            }
            if (laser_count > 0) {
                special_ammu_notice(screen, SAN_font, laser_count);
                if (keystates[SDLK_n] && laser_delay_counter == 0) {
                    special_ammu_effect(screen, our_spaceshipx, our_spaceshipy, boss_fight);
                    laser_count--;
                    laser_delay_counter = 10;
                }
            }
            if (laser_delay_counter > 0) {
                laser_delay_counter--;
            }

            //========================================================================


            //=========================explosion=======================================
            if (explosion(screen, game_over, boss_fight, our_spaceshipx, our_spaceshipy, our_explo_frame,
                          boss_explo_frame) == 1) {
                last_menu = true;
            }
            //========================================================================


            if (keystates[SDLK_SPACE]) {
                if (arrow_delay % 10 == 0 && our_spaceship_bullet > 0) {
                    arrow_number = make_arrow_ingame(screen, our_spaceshipx, our_spaceshipy, arrow_number);
                    if (volume == true) {
                        Mix_PlayChannel(-1, our_shot, 0);
                    }
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
                enemy_spaceships_start_pos(screenwidth, &enemy_spaceship_delay, max_enemies_enter_delay,
                                           max_enemies_count, enemy_type);
            }

            enemy_spaceships_move(screenheight, our_spaceshipx, &our_spaceship_heart);
            show_enemy_spaceships(screen, enemy_type);
            enemy_shooting(enemy_type, enemy_shot, &volume);
            move_enemy_arrow(screen);

            if (boss_fight) {
                if (boss[0].y <= 150) {
                    boss_enters();
                } else {
                    boss_x_change(screenwidth, boss_size, our_spaceshipx);
                    enemy_boss_shooting(boss_shot, &volume);

                    if (collision(boss_fight, explosion_sound, &volume) == 1) {
                        our_spaceship_heart--;
                    }
                    show_boss_health_bar(screen);
                }
                show_boss(screen, boss_size);
                boss_sensors_position(screen);
                boss_collision_check();
                if (boss[0].hitpoint <= 0) {
                    level++;
                    show_level_frame++;
                    level_difficulity(level, &max_enemies_count, &max_enemies_enter_delay, &enemy_type);
                    boss_fight = false;
                    if (volume == true) {
                        Mix_PlayChannel(-1, explosion_sound, 0);
                    }
                    boss_explo_frame = 1;
                    //  destroy_the_boss();
                }
            }
            move_enemy_boss_arrow(screen, screenheight);

            if (show_level_frame > 0 && show_level_frame < 100) {
                float counter = show_level_frame / 2 + 1;
                show_level_num(level, show_level_frame, screen, counter);
                show_level_frame++;
                if (show_level_frame == 99) {
                    show_level_frame = 0;
                }
            }

            if (keystates[SDLK_UP]) {
                speed_change(1, &max_enemies_enter_delay);
            }
            if (keystates[SDLK_DOWN]) {
                speed_change(-1, &max_enemies_enter_delay);
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
            sensors_position(screen, our_spaceshipx, our_spaceshipy, enemy_type);

            if (collision(boss_fight, explosion_sound, &volume) == 1) {
                our_spaceship_heart--;
            }

            if (our_spaceship_heart <= 0) {
                game_over = true;
                if (volume == true) {
                    Mix_PlayChannel(-1, explosion_sound, 0);
                }
            }

            if (game_over) {
                our_explo_frame++;
            }
            if (boss_explo_frame > 0) {
                boss_explo_frame++;
            }
            if (boss_explo_frame == 26) {
                boss_explo_frame = 0;
            }

            if (frame >= (100 - (star[0].yv * 5)) && boss_fight == false) {
                frame = 0;
                score++;
            }

            if (score % 30 == 0 && score != 0 && boss_fight == false) {
                boss_first_initialize(screenwidth, boss_size, level);
                boss_fight = true;
            }

            if (keystates[SDLK_ESCAPE]) {
                middle_menu = true;
            }

            frame++;
        }

        if (middle_menu == true) {

            boxRGBA(screen, 0, 0, screenwidth, screenheight, 45, 45, 45, 200);
            apply_surface(310, 150, paused_message, screen);
            boxRGBA(screen, 350, screenheight - 150, 650, screenheight - 50, 255, 75, 0, 200);
            boxRGBA(screen, 350, screenheight - 275, 650, screenheight - 175, 0, 175, 255, 200);
            boxRGBA(screen, 350, screenheight - 400, 650, screenheight - 300, 0, 175, 255, 200);
            apply_surface(420, screenheight - 367, resume, screen);
            apply_surface(415, screenheight - 242, middle_menu_restart, screen);
            apply_surface(460, screenheight - 117, middle_menu_exit, screen);
            if (middle_menu_move_pointer(&middle_menu_pointer_y) == false) {
                return  0;
            }
            filledCircleRGBA(screen, middle_menu_pointer_x, middle_menu_pointer_y, 5, 0, 254, 0, 200);


            if (keystates[SDLK_RCTRL]) {
                if (middle_menu_pointer_y == 650) {
                    middle_menu = false;
                    SDL_Delay(1000);
                }
                if (middle_menu_pointer_y == 775) {
                    arrow_number = 0; // arrow's number that after pressing the space key throw
                    our_spaceship_heart = 3; // the spaceship's heart in the beginning
                    our_spaceship_bullet = 300; // the spaceship's bullet in the beginning
                    score = 0;
                    level = 1;
                    frame = 0;
                    total_stars = 80;// total number of stars that made till now
                    our_spaceshipx = 450;
                    our_spaceshipy = 870;
                    our_explo_frame = 2;
                    boss_explo_frame = 0;
                    boss_size = 200;
                    max_enemies_count = 1;
                    max_enemies_enter_delay = 300;
                    show_level_frame = 1;
                    power_up_drop_timer = (rand() % 300) + 500;
                    power_up_type = rand() % 3;
                    enemy_type = "enemyspaceship.png";
                    stars_speed = 2;
                    our_spaceship_right_v = 0;
                    our_spaceship_left_v = 0;
                    laser_count = 0;
                    special_ammu[0].ingame = false;
                    extra_heart[0].ingame = false;
                    extra_bullet[0].ingame = false;
                    red_meteorite[0].ingame = false;
                    last_music_play = true;
                    last_menu_highscore_image = false;
                    special_ammu[0].yv = 2;
                    extra_heart[0].yv = 2;
                    extra_bullet[0].yv = 2;
                    red_meteorite[0].yv = 6;
                    boss_fight = false;
                    enemy_spaceship_delay = (rand() % max_enemies_enter_delay / 10) + 100;
                    heart_value = make_toolbar_informations(heart_value, toolbar_font, textcolor, our_spaceship_heart);
                    bullet_value = make_toolbar_informations(bullet_value, toolbar_font, textcolor, our_spaceship_bullet);
                    score_value = make_toolbar_informations(score_value, toolbar_font, textcolor, score);
                    highscore_value = make_toolbar_informations(highscore_value, toolbar_font, textcolor, highscore);
                    for (int i = 0; i < 1000; i++) {
                        arrow[i].ingame = false;
                    }
                    for (int i = 0; i < 80; i++) {
                        star[i].yv = 2;
                    }
                    for (int i = 0; i < 15; i++) {
                        classic_enemies[i].ingame = false;
                        classic_enemies[i].yv = 3;
                        classic_enemies[i].xv = 0;
                    }
                    for (int i = 0; i < 1000; i++) {
                        enemy_arrow[i].ingame = false;
                        enemy_arrow[i].x_velocity = 0;
                        enemy_arrow[i].y_velocity = 6;
                        boss_arrow[i].ingame = false;
                        boss_arrow[i].x_velocity = 0;
                        boss_arrow[i].y_velocity = 6;
                    }

                    for (int i = 0; i < 5; i++) {
                        our[i].ingame = true; //make our spaceship sensor in game
                    }
                    first_menu = false;
                    last_menu = false;
                    middle_menu = false;
                    game_over = false;
                    gameover_y = -400;
                    last_menu_pointer_x = 340;
                    last_menu_pointer_y = 775;

                }

                if (middle_menu_pointer_y == 900) {
                    return 0;
                }
            }
        }

        if (last_menu == true) {

            if (last_music_play == true) {
                if (volume == true) {
                    Mix_PlayChannel(-1, gameover_sound, 0);
                }
            }
            score_value = make_toolbar_informations(score_value, menu_font, textcolor, score);
            boxRGBA(screen, 0, 0, screenwidth, screenheight, 45, 45, 45, 255);
            if (gameover_y != 50) {
                gameover_y += 1;
                apply_surface(250, gameover_y, gameover, screen);
            }
            if (gameover_y == 50) {
                apply_surface(250, gameover_y, gameover, screen);
            }
            if (gameover_y == 0) {
                last_music_play = false;
            }
            if (gameover_y == 0) {
                last_music_play = false;
            }
            boxRGBA(screen, 190, screenheight - 400, 490, screenheight - 300, 0, 175, 255, 200);
            boxRGBA(screen, 510, screenheight - 400, 810, screenheight - 300, 0, 175, 255, 200);
            boxRGBA(screen, 350, screenheight - 275, 650, screenheight - 175, 255, 75, 0, 200);
            boxRGBA(screen, 350, screenheight - 150, 650, screenheight - 50, 255, 75, 0, 200);
            apply_surface(258, screenheight - 367, last_menu_score, screen);
            apply_surface(410, screenheight - 242, restart, screen);
            apply_surface(455, screenheight - 117, last_menu_exit, screen);
            if (last_menu_highscore_image == true) {
                apply_surface(425, screenheight - 600, new_highscore_image, screen);
            }
            if (score < 10) {
                apply_surface(637, screenheight - 367, score_value, screen);
            }
            if (score < 100 && score >= 10) {
                apply_surface(627, screenheight - 367, score_value, screen);
            }
            if (score < 1000 && score >= 100) {
                apply_surface(617, screenheight - 367, score_value, screen);
            }
            if (score < 10000 && score >= 1000) {
                apply_surface(607, screenheight - 367, score_value, screen);
            }
            if (score < 100000 && score >= 10000) {
                apply_surface(597, screenheight - 367, score_value, screen);
            }
            if (score < 1000000 && score >= 100000) {
                apply_surface(587, screenheight - 367, score_value, screen);
            }
            if (score < 10000000 && score >= 1000000) {
                apply_surface(577, screenheight - 367, score_value, screen);
            }
            if (last_menu_move_pointer(&last_menu_pointer_x, &last_menu_pointer_y) == false) {
                return  0;
            }
            filledCircleRGBA(screen, last_menu_pointer_x, last_menu_pointer_y, 5, 0, 254, 0, 200);

            if (keystates[SDLK_RCTRL]) {
                if (last_menu_pointer_y == 900) {
                    return 0;
                }

                if (last_menu_pointer_y == 775) {
                    arrow_number = 0; // arrow's number that after pressing the space key throw
                    our_spaceship_heart = 3; // the spaceship's heart in the beginning
                    our_spaceship_bullet = 300; // the spaceship's bullet in the beginning
                    score = 0;
                    level = 1;
                    frame = 0;
                    total_stars = 80;// total number of stars that made till now
                    our_spaceshipx = 450;
                    our_spaceshipy = 870;
                    our_explo_frame = 2;
                    boss_explo_frame = 0;
                    boss_size = 200;
                    max_enemies_count = 1;
                    max_enemies_enter_delay = 300;
                    show_level_frame = 1;
                    power_up_drop_timer = (rand() % 300) + 500;
                    power_up_type = rand() % 3;
                    enemy_type = "enemyspaceship.png";
                    stars_speed = 2;
                    our_spaceship_right_v = 0;
                    our_spaceship_left_v = 0;
                    laser_count = 0;
                    special_ammu[0].ingame = false;
                    extra_heart[0].ingame = false;
                    extra_bullet[0].ingame = false;
                    red_meteorite[0].ingame = false;
                    last_music_play = true;
                    last_menu_highscore_image = false;
                    special_ammu[0].yv = 2;
                    extra_heart[0].yv = 2;
                    extra_bullet[0].yv = 2;
                    red_meteorite[0].yv = 6;
                    boss_fight = false;
                    enemy_spaceship_delay = (rand() % max_enemies_enter_delay / 10) + 100;
                    heart_value = make_toolbar_informations(heart_value, toolbar_font, textcolor, our_spaceship_heart);
                    bullet_value = make_toolbar_informations(bullet_value, toolbar_font, textcolor, our_spaceship_bullet);
                    score_value = make_toolbar_informations(score_value, toolbar_font, textcolor, score);
                    highscore_value = make_toolbar_informations(highscore_value, toolbar_font, textcolor, highscore);
                    for (int i = 0; i < 1000; i++) {
                        arrow[i].ingame = false;
                    }
                    for (int i = 0; i < 80; i++) {
                        star[i].yv = 2;
                    }
                    for (int i = 0; i < 15; i++) {
                        classic_enemies[i].ingame = false;
                        classic_enemies[i].yv = 3;
                        classic_enemies[i].xv = 0;
                    }
                    for (int i = 0; i < 1000; i++) {
                        enemy_arrow[i].ingame = false;
                        enemy_arrow[i].x_velocity = 0;
                        enemy_arrow[i].y_velocity = 6;
                        boss_arrow[i].ingame = false;
                        boss_arrow[i].x_velocity = 0;
                        boss_arrow[i].y_velocity = 6;
                    }
                    for (int i = 0; i < 5; i++) {
                        our[i].ingame = true; //make our spaceship sensor in game
                    }
                    first_menu = false;
                    last_menu = false;
                    middle_menu = false;
                    game_over = false;
                    gameover_y = -400;
                    last_menu_pointer_x = 340;
                    last_menu_pointer_y = 775;
                }
            }
        }

        SDL_Flip(screen);
        SDL_Delay(5);
    }

    return 0;
}
