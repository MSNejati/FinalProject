#include <iostream>
using namespace std;

void speed_change(int comm)
{
    if(comm == 1)
    {
        for(int i = 0 ; i < 80 ; i++)
        {
            star[i].yv += 0.5;
        }
        for(int i = 0 ; i < 15 ; i++)
        (
            if(classic_enemies[i].ingame)
            {
                classic_enemies[i].yv += 0.5;
            }
        )
        for(int i = 0 ; i < 100 ; i++)
        {
            if(enemy_arrow[i].ingame)
            {
                enemy_arrow[i].y_velocity += 0.5;
            }
        }
    }
    if(comm == -1)
    {
        for(int i = 0 ; i < 80 ; i++)
        {
            star[i].yv -= 0.5;
        }
        for(int i = 0 ; i < 15 ; i++)
        (
            if(classic_enemies[i].ingame)
            {
                classic_enemies[i].yv -= 0.5;
            }
        )
        for(int i = 0 ; i < 100 ; i++)
        {
            if(enemy_arrow[i].ingame)
            {
                enemy_arrow[i].y_velocity -= 0.5;
            }
        }
    }
}
