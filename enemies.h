#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <cstdlib>
#include <ctime>
#include "applysurface.h"

using namespace std;

struct enemy_spaceships
{
    int x;
    int y;
    int xv;
    float yv = 3;
    int shoot_delay = (rand() % 70) + 60;
    int hitpoint = 1;
    int explosion_counter = 1;
    bool ingame = false;
}classic_enemies[15],boss[1];

struct enemy_shot {
	int x;
	int y;
	int x_velocity = 0;
	float y_velocity = 6; // i don't use it now but maybe we use it later
	bool ingame = false;
}enemy_arrow[10000] ,boss_arrow[100];



void enemy_spaceships_start_pos(int screenwidth ,int * enemy_spaceship_delay ,int max_enemies_enter_delay ,int max_enemies_count ,string enemy_type)
{
    int enemy_spaceship_count;
    if(*enemy_spaceship_delay == 0)
    {
        *enemy_spaceship_delay = (rand() % max_enemies_enter_delay) + 120;
        enemy_spaceship_count = (rand() % max_enemies_count) + 1;
        for(int i = 0 ; i < enemy_spaceship_count ; i++)
        {
            for(int j = 0 ; j < 15 ; j++)
            {
                if(classic_enemies[j].ingame == false)
                {
                    for(int k = 0 ; k < j ; k++)
                    {
                        do
                        {
                            classic_enemies[j].x = (rand() % (screenwidth)/100) * 100;
                        }
                        while(classic_enemies[k].x == classic_enemies[j].x && classic_enemies[k].y < 100);
                    }
                    if(enemy_type == "enemyspaceship.png")
                    {
                        classic_enemies[j].hitpoint = 1;
                    }
                    if(enemy_type == "enemyspaceship2.png")
                    {
                        classic_enemies[j].hitpoint = 2;
                    }
                    classic_enemies[j].y = -100;
                    classic_enemies[j].ingame = true;
                    break;
                }
            }
        }
    }
    else
    {
        *(enemy_spaceship_delay) = *enemy_spaceship_delay - 1;
    }
}

void enemy_spaceships_move(int screenheight ,int our_spaceshipx, int * heart)
{
    for(int j = 0 ; j < 15 ; j++)
    {
       if(classic_enemies[j].ingame)
       {
            classic_enemies[j].y += classic_enemies[j].yv;
            if(classic_enemies[j].y >= screenheight)
            {
                classic_enemies[j].ingame = false;
		*heart -= 1;
            }
            if(classic_enemies[j].x < our_spaceshipx)
            {
                classic_enemies[j].xv = 1;
            }
            if(classic_enemies[j].x > our_spaceshipx)
            {
                classic_enemies[j].xv = -1;
            }
            if(classic_enemies[j].x == our_spaceshipx)
            {
                classic_enemies[j].xv = 0;
            }
            classic_enemies[j].x += classic_enemies[j].xv;
       }
    }
}

void show_enemy_spaceships(SDL_Surface * screen ,string enemy_type)
{
    SDL_Surface* enemyspaceship;
    for(int j = 0 ; j < 15 ; j++)
    {
        if(classic_enemies[j].ingame)
        {
            enemyspaceship = load_enemyspaceship(enemy_type);
            apply_surface(classic_enemies[j].x ,classic_enemies[j].y , enemyspaceship ,screen );
        }
    }
}


void enemy_shooting(string enemy_type)
{
    for(int i = 0 ; i < 15 ; i++)
    {
        if(classic_enemies[i].ingame)
        {
            if(classic_enemies[i].shoot_delay == 0)
            {
                classic_enemies[i].shoot_delay = (rand() % 70) + 60;
                if(enemy_type == "enemyspaceship.png")
                {
                    for(int j = 0 ; j < 10000 ; j++)
                    {
                        if(enemy_arrow[j].ingame == false)
                        {
                            enemy_arrow[j].ingame = true;
                            enemy_arrow[j].x = classic_enemies[i].x + 50;
                            enemy_arrow[j].y = classic_enemies[i].y + 80;
                            break;
                        }
                    }
                }
                if(enemy_type == "enemyspaceship2.png")
                {
                    for(int k = 0 ; k < 3 ; k++)
                    {
                        if(k == 0)
                        {
                            for(int j = 0 ; j < 10000 ; j++)
                            {
                                if(enemy_arrow[j].ingame == false)
                                {
                                    enemy_arrow[j].ingame = true;
                                    enemy_arrow[j].x = classic_enemies[i].x + 20;
                                    enemy_arrow[j].y = classic_enemies[i].y + 100;
                                    enemy_arrow[j].x_velocity = -2;
                                    break;
                                }
                            }
                        }
                        if(k == 1)
                        {
                            for(int j = 0 ; j < 10000 ; j++)
                            {
                                if(enemy_arrow[j].ingame == false)
                                {
                                    enemy_arrow[j].ingame = true;
                                    enemy_arrow[j].x = classic_enemies[i].x + 80;
                                    enemy_arrow[j].y = classic_enemies[i].y + 100;
                                    enemy_arrow[j].x_velocity = 2;
                                    break;
                                }
                            }
                        }
                        if(k == 2)
                        {
                            for(int j = 0 ; j < 10000 ; j++)
                            {
                                if(enemy_arrow[j].ingame == false)
                                {
                                    enemy_arrow[j].ingame = true;
                                    enemy_arrow[j].x = classic_enemies[i].x + 50;
                                    enemy_arrow[j].y = classic_enemies[i].y + 100;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                classic_enemies[i].shoot_delay--;
            }
        }
    }
}



void move_enemy_arrow (SDL_Surface *screen) {

	for (int i = 0; i < 10000; i++) {
		if (enemy_arrow[i].y >= 0 && enemy_arrow[i].ingame == true) {
			enemy_arrow[i].y += enemy_arrow[i].y_velocity;
			enemy_arrow[i].x += enemy_arrow[i].x_velocity;
			filledCircleRGBA(screen,enemy_arrow[i].x, enemy_arrow[i].y, 3, 255, 255, 0, 255);
		}
		if (enemy_arrow[i].y < -2 && enemy_arrow[i].ingame == true)
		{
            enemy_arrow[i].ingame = false;

		}
	}
}

void boss_first_initialize(int screenwidth ,int boss_size)
{
    boss[0].x = (screenwidth - boss_size) / 2;
    boss[0].y = -1*boss_size;
    boss[0].yv = 3;
    boss[0].xv = 2;
    boss[0].hitpoint = 50;
    boss[0].ingame = true;
}

void boss_enters()
{
    boss[0].y += boss[0].yv;
}

void show_boss(SDL_Surface * screen ,int boss_size)
{
    SDL_Surface* boss_spaceship;
    boss_spaceship = load_enemyspaceship("big_enemy.png");
    apply_surface(boss[0].x ,boss[0].y , boss_spaceship ,screen );

}

void boss_x_change(int screenwidth , int boss_size)
{
    boss[0].x += boss[0].xv;

    if(boss[0].x <= 0 || boss[0].x >= screenwidth - boss_size)
    {
        boss[0].xv *= -1;
    }
}


void enemy_boss_shooting()
{
            if(boss[0].shoot_delay == 0)
            {
                boss[0].shoot_delay = (rand() % 70) + 60;
                for(int i = 0 ; i < 5 ; i++)
                {
                    for(int j = 0 ; j < 100 ; j++)
                    {
                        if(boss_arrow[j].ingame == false)
                        {
                            boss_arrow[j].ingame = true;
                            if(i == 0)
                            {
                                boss_arrow[j].x = boss[0].x + 20;
                                boss_arrow[j].y = boss[0].y + 200;
                                boss_arrow[j].x_velocity = 0;
                            }
                            if(i == 1)
                            {
                                boss_arrow[j].x = boss[0].x + 80;
                                boss_arrow[j].y = boss[0].y + 200;
                                boss_arrow[j].x_velocity = -2;
                            }
                            if(i == 2)
                            {
                                boss_arrow[j].x = boss[0].x + 100;
                                boss_arrow[j].y = boss[0].y + 200;
                                boss_arrow[j].x_velocity = 0;
                            }
                            if(i == 3)
                            {
                                boss_arrow[j].x = boss[0].x + 120;
                                boss_arrow[j].y = boss[0].y + 200;
                                boss_arrow[j].x_velocity = 2;
                            }
                            if(i == 4)
                            {
                                boss_arrow[j].x = boss[0].x + 180;
                                boss_arrow[j].y = boss[0].y + 200;
                                boss_arrow[j].x_velocity = 0;
                            }
                            break;
                        }
                    }
                }
            }
            else
            {
                boss[0].shoot_delay--;
            }
}


void move_enemy_boss_arrow (SDL_Surface *screen ,int screenheight)
{
	for (int i = 0; i < 100; i++) {
		if (boss_arrow[i].y >= 0 && boss_arrow[i].ingame == true)
		 {
			boss_arrow[i].y += boss_arrow[i].y_velocity;
			boss_arrow[i].x += boss_arrow[i].x_velocity;
			filledCircleRGBA(screen,boss_arrow[i].x, boss_arrow[i].y, 3, 255, 255, 0, 255);
		}
		if (boss_arrow[i].y > screenheight && boss_arrow[i].ingame == true)
		{
            boss_arrow[i].ingame = false;

		}
	}
}



void show_boss_health_bar(SDL_Surface * screen)
{
    boxRGBA(screen ,245 ,115 ,755 ,145 ,255 ,255 ,0 ,200);
    boxRGBA(screen ,250 ,120 ,750 ,140 ,0 ,0 ,0 ,200);
    boxRGBA(screen ,250 ,120 ,250 + boss[0].hitpoint * 10 ,140 ,255 ,0 ,0 ,200);
}

void destroy_the_boss()
{
    for(int i = 0 ; i < 100 ;i++)
    {
        boss_arrow[i].ingame = false;
    }

}



