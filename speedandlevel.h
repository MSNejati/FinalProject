#include <iostream>
#include "background.h"
#include "sensorsandcollision.h"

using namespace std;

void speed_change(int comm)
{
    if(comm == 1)
    {
        for(int i = 0 ; i < 80 ; i++)
        {
            if(star[i].yv <= 15)
            {
                star[i].yv += 0.5;
            }
        }
        for(int i = 0 ; i < 15 ; i++)
        {
            if(classic_enemies[i].yv <= 16)
            {
                classic_enemies[i].yv += 0.5;
            }
        }
        for(int i = 0 ; i < 100 ; i++)
        {
            if(enemy_arrow[i].y_velocity <= 19)
            {
                enemy_arrow[i].y_velocity += 0.5;
            }
        }
    }
    if(comm == -1)
    {
        for(int i = 0 ; i < 80 ; i++)
        {
            if(star[i].yv > 2)
            {
                star[i].yv -= 0.5;
            }
        }
        for(int i = 0 ; i < 15 ; i++)
        {
            if(classic_enemies[i].yv > 3)
            {
                classic_enemies[i].yv -= 0.5;
            }
        }
        for(int i = 0 ; i < 100 ; i++)
        {
            if(enemy_arrow[i].y_velocity > 6)
            {
                enemy_arrow[i].y_velocity -= 0.5;
            }
        }
    }
}



void level_difficulity(int level ,int * max_enemies_count ,int * max_enemies_enter_delay ,string * enemy_type)
{
    if(level <= 3)
    {
        *(max_enemies_count) = level;
        *(max_enemies_enter_delay) -= level*20;
    }
    else
    {
        *(enemy_type) = "enemyspaceship2.png";
    }
}






