#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "enemies.h"
#include "throw_arrows.h"

struct sensors
{
    int x1;
    int y1;
    int x2;
    int y2;
    bool ingame = false;
}our[5],enemies[15][5];

void sensors_position(SDL_Surface * screen ,int our_spaceshipx ,int our_spaceshipy)
{
    our[0].x1 = our_spaceshipx + 40;
    our[0].y1 = our_spaceshipy + 5;
    our[0].x2 = our_spaceshipx + 60;
    our[0].y2 = our_spaceshipy + 20;
    our[1].x1 = our_spaceshipx + 30;
    our[1].y1 = our_spaceshipy + 20;
    our[1].x2 = our_spaceshipx + 70;
    our[1].y2 = our_spaceshipy + 50;
    our[2].x1 = our_spaceshipx + 20;
    our[2].y1 = our_spaceshipy + 50;
    our[2].x2 = our_spaceshipx + 80;
    our[2].y2 = our_spaceshipy + 70;
    our[3].x1 = our_spaceshipx + 0;
    our[3].y1 = our_spaceshipy + 70;
    our[3].x2 = our_spaceshipx + 100;
    our[3].y2 = our_spaceshipy + 90;
    our[4].x1 = our_spaceshipx + 40;
    our[4].y1 = our_spaceshipy + 90;
    our[4].x2 = our_spaceshipx + 60;
    our[4].y2 = our_spaceshipy + 100;
    for (int i = 0 ; i < 15 ; i++)
    {
        if(classic_enemies[i].ingame)
        {
            enemies[i][0].x1 = classic_enemies[i].x + 0;
            enemies[i][0].y1 = classic_enemies[i].y + 20;
            enemies[i][0].x2 = classic_enemies[i].x + 100;
            enemies[i][0].y2 = classic_enemies[i].y + 40;
            enemies[i][0].ingame = true;
            enemies[i][1].x1 = classic_enemies[i].x + 15;
            enemies[i][1].y1 = classic_enemies[i].y + 40;
            enemies[i][1].x2 = classic_enemies[i].x + 80;
            enemies[i][1].y2 = classic_enemies[i].y + 50;
            enemies[i][1].ingame = true;
            enemies[i][2].x1 = classic_enemies[i].x + 25;
            enemies[i][2].y1 = classic_enemies[i].y + 50;
            enemies[i][2].x2 = classic_enemies[i].x + 70;
            enemies[i][2].y2 = classic_enemies[i].y + 60;
            enemies[i][2].ingame = true;
            enemies[i][3].x1 = classic_enemies[i].x + 35;
            enemies[i][3].y1 = classic_enemies[i].y + 60;
            enemies[i][3].x2 = classic_enemies[i].x + 60;
            enemies[i][3].y2 = classic_enemies[i].y + 70;
            enemies[i][3].ingame = true;
            enemies[i][4].x1 = classic_enemies[i].x + 40;
            enemies[i][4].y1 = classic_enemies[i].y + 70;
            enemies[i][4].x2 = classic_enemies[i].x + 55;
            enemies[i][4].y2 = classic_enemies[i].y + 80;
            enemies[i][4].ingame = true;
        }
        if(!classic_enemies[i].ingame)
        {
            for(int j = 0 ; j < 5 ; j++)
            {
                enemies[i][j].ingame = false;
            }
        }
    }
}


void collision()
{
    for(int i = 0 ; i < 15 ; i++)
    {
        for(int j = 0 ; j < 5 ; j++)
        {
            if(enemies[i][j].ingame == true )
            {
                for(int k = 0 ; k < 100 ; k++)
                {
                    if(arrow[k].ingame == true )
                    {
                        if(arrow[k].x > enemies[i][j].x1)
                        {
                            if(arrow[k].x < enemies[i][j].x2)
                            {
                                if(arrow[k].y > enemies[i][j].y1)
                                {
                                    if(arrow[k].y < enemies[i][j].y2)
                                    {
                                        for(int p = 0 ; p < 5 ; p++)
                                        {
                                            enemies[i][p].ingame = false;
                                        }
                                        classic_enemies[i].ingame = false;
                                        arrow[k].ingame = false;

                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}




