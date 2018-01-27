#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <cstdlib>
#include <ctime>

using namespace std;

struct enemy_spaceships
{
    int x;
    int y;
    int yv;
    bool ingame = false;
}classic_enemies[15];


void enemy_spaceships_start_pos(int screenwidth ,int * enemy_spaceship_delay)
{
    int enemy_spaceship_count;
    if(*enemy_spaceship_delay == 0)
    {
        *enemy_spaceship_delay = (rand() % 200) + 100;
        enemy_spaceship_count = (rand() % 3) + 1;
        for(int i = 0 ; i < enemy_spaceship_count ; i++)
        {
            for(int j = 0 ; j < 15 ; j++)
            {
                if(classic_enemies[j].ingame == false)
                {
                    classic_enemies[j].x = (rand() % (screenwidth)/100) * 100;
                    classic_enemies[j].y = -100;
                    classic_enemies[j].yv = 3;
                    classic_enemies[j].ingame = true;
                    break;
                }
            }
        }
    }
    else
    {
        *(enemy_spaceship_delay) = *enemy_spaceship_delay - 1;
        cout << *enemy_spaceship_delay << endl;
    }
}

void enemy_spaceships_move(int screenheight)
{
    for(int j = 0 ; j < 15 ; j++)
    {
       if(classic_enemies[j].ingame)
       {
            classic_enemies[j].y += classic_enemies[j].yv;
            if(classic_enemies[j].y >= screenheight)
            {
                classic_enemies[j].ingame = false;
            }
       }
    }
}

void show_enemy_spaceships(SDL_Surface * screen)
{
    for(int j = 0 ; j < 15 ; j++)
    {
        if(classic_enemies[j].ingame)
        {
            filledCircleRGBA(screen ,classic_enemies[j].x ,classic_enemies[j].y ,10 ,255 ,255 ,255 ,255);
        }
    }
}
